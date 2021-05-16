#include "Image.h"

namespace MinUI
{

/*
Image::Image()
 : m_id(""), m_position({0, 0}), m_dimension({0, 0}),
   m_data_p(nullptr), m_pixmap(0)
{}
*/

Image::Image(std::string id, Vector2f position, Vector2i size, BYTE* data)
	: m_id(id), m_position(position), m_size(size), m_data_p(nullptr),
	  m_image_p(nullptr), m_setup(false)
{
	loadFromData(data, size.x, size.y);
}

Image::Image(std::string id, Vector2f position, std::string path)
	: m_id(id), m_position(position), m_size({0, 0}), m_data_p(nullptr),
m_image_p(nullptr), m_setup(false)
{
	loadFromBMP(path);
}

Image::Image(std::string id, Vector2f position, Vector2i size)
	: m_id(id), m_position(position), m_size(size),
	  m_image_p(nullptr), m_setup(false)
{
	m_data_p = new BYTE[4 * size.x * size.y];
	for (int i = 0; i < m_size.x * m_size.y * 4 ; i++)
		m_data_p[i] = 0;
}

Image& Image::operator=(const Image &image)
{
	if (this != &image) {
		m_size = image.m_size;

		BYTE * temp = m_data_p;
		m_data_p = new BYTE[4 * m_size.x * m_size.y];
		std::copy(image.m_data_p, image.m_data_p
		          + (4 * m_size.x * m_size.y), m_data_p);


		if (temp != nullptr)
			delete [] temp;

		m_setup = false;
	}

	return *this;
}


Image::Image(const Image &image)
	: m_size({0, 0}), m_data_p(NULL)
{
	*this = image; // overloaded '=' is used
}

void Image::render(X11Context& context, Font& font)
{
	if (!m_setup) {

		m_image_p = XCreateImage(context.display_p, context.info.visual, 24, ZPixmap,
	                         0, (char *) m_data_p, m_size.x, m_size.y, 8, 0);
		m_setup = true;
	}

	//TODO: HERE

	 XPutImage(context.display_p, context.buffer, context.gc, m_image_p, 0, 0,
	          (m_position.x * GRID_SIZE), (m_position.y * GRID_SIZE), m_size.x, m_size.y);
}

void Image::update(InputState& input_state) {}

Image * Image::clone()
{
	return new Image(*this);
}

std::string Image::id()
{
	return m_id;
}

void Image::reallocate(int width, int height)
{
	m_size = {width, height};

	BYTE * temp = m_data_p;

	m_data_p = new BYTE[4 * width * height];

	std::fill(m_data_p, m_data_p + 4 * width * height,  0);

	//for (int i = 0; i < width * height * 4 ; i++)
	//	m_data_p[i] = 0;

	delete [] temp;

	std::free(m_image_p);

	m_setup = false;
}

void Image::setData(BYTE * raw_data, bool flip)
{
	for (int i = 0; i < m_size.x; i++)
		for (int j = 0; j < m_size.y; j++) {

			int position = m_size.x * j + i;

			BYTE r = raw_data[3 * position];
			BYTE g = raw_data[3 * position + 1];
			BYTE b = raw_data[3 * position + 2];

			if (flip)
				position = m_size.x * (m_size.y - j - 1) + i;

			m_data_p[4 * position]     = b;
			m_data_p[4 * position + 1] = g;
			m_data_p[4 * position + 2] = r;
			m_data_p[4 * position + 3] = 0;
		}
}

void Image::loadFromData(BYTE * raw_data, int width, int height, bool flip)
{
	m_size = {width, height};

	// Reallocate
	reallocate(width, height);

	// TODO if (m_size.x != width || m_size.y != height)
	setData(raw_data);
}

void Image::loadFromBMP(std::string filename)
{

	std::ifstream file(filename, std::ios::binary);

	if (!file.is_open()) {
		std::cerr << " Unable to open '" << filename << "'" << std::endl;
		return;
	}

	int header_size = 54;

	char* header = new char[header_size];

	file.seekg(0, std::ios::beg);
	file.read(header, header_size);

	////////////////////////////////////////////////////////////////////////////

	int width, height;

	BYTE lc, rc;

	lc = header[18];
	rc = header[19];
	width = ((int) lc) + 256 * ((int) rc);

	lc = header[22];
	rc = header[23];
	height = ((int) lc) + 256 * ((int) rc);

	////////////////////////////////////////////////////////////////////////////

	lc = header[30];
	rc = header[31];
	int compression = ((int) lc) + 256 * ((int) rc);

	if (compression != 0) {
		std::cerr << " Only uncompressed BMPs are supported" << std::endl;
		throw std::exception();
	}

	////////////////////////////////////////////////////////////////////////////

	lc = header[28];
	rc = header[29];
	int bpp = ((int) lc) + 256 * ((int) rc);

	if (bpp != 24) {
		std::cerr << " Only 24bit RGB images are supported" << std::endl;
		throw std::exception();
	}

	////////////////////////////////////////////////////////////////////////////

	lc = header[10];
	rc = header[11];
	int offset = ((int) lc) + 256 * ((int) rc);

	file.seekg(offset, std::ios::beg);      // optional

	////////////////////////////////////////////////////////////////////////////

	int row_size = std::ceil(((float) bpp * width) / 32) * 4;

	////////////////////////////////////////////////////////////////////////////

	char * raw_data = new char[width * row_size];

	file.read(raw_data, row_size * height);

	loadFromData((BYTE *)raw_data, width, height, 1);

	delete [] header;
	delete [] raw_data;

	////////////////////////////////////////////////////////////////////////////

	file.close();
}

Image::~Image()
{
	if (m_image_p != nullptr) {
		//XDestroyImage(m_image_p); // frees m_data_p too
		std::free(m_image_p);
		delete [] m_data_p;
	}
}

}

