#include "Frame.h"

namespace MinUI
{
void Frame::sampleAlongX(float ratio)
{
	int dest_width = std::floor(ratio * m_w);

	BYTE * sampled = new BYTE[dest_width * m_h];

	for (int j = 0; j < m_h; j++)
		for (int i = 0; i < dest_width; i++) {
			float x_a = i / ratio;
			float x_b = (i + 1) / ratio;

			float value = 0;

			for (int k = std::ceil(x_a); k < std::floor(x_b); k++)
				value += (*this)(k, j);

			value += (std::ceil(x_a) - x_a) * (*this)(std::floor(x_a), j);
			value += (x_b - std::floor(x_b)) * (*this)(std::floor(x_b), j);

			value /= (x_b - x_a);

			sampled[j * dest_width + i] = value;
		}

	m_w = dest_width;

	BYTE * temp = m_data;
	m_data = sampled;
	delete [] temp;
}

void Frame::sampleAlongY(float ratio)
{
	int dest_height = std::floor(ratio * m_h);

	BYTE * sampled = new BYTE[dest_height * m_h];

	for (int j = 0; j < dest_height; j++)
		for (int i = 0; i < m_w; i++) {
			float y_a = j / ratio;
			float y_b = (j + 1) / ratio;

			float value = 0;

			for (int k = std::ceil(y_a); k < std::floor(y_b); k++)
				value += (*this)(i, k);

			value += (std::ceil(y_a) - y_a) * (*this)(i, std::floor(y_a));
			value += (y_b - std::floor(y_b)) * (*this)(i, std::floor(y_b));

			value /= (y_b - y_a);

			sampled[j * m_w + i] = value;
		}



	m_h = dest_height;

	BYTE * temp = m_data;
	m_data = sampled;
	delete [] temp;
}


Frame::Frame()
	:  m_data(NULL), m_w(0), m_h(0)
{}

Frame::Frame(int width, int height)
	: m_w(width), m_h(height)
{
	m_data = new BYTE[width * height];
}

Frame& Frame::operator=(const Frame &frame)
{
	if (this != &frame) {
		m_w = frame.m_w;
		m_h = frame.m_h;

		BYTE * temp = m_data;
		m_data = new BYTE[m_w * m_h];
		std::copy(frame.m_data, frame.m_data + (m_w * m_h), m_data);

		delete [] temp;
	}

	return *this;
}

Frame::Frame(const Frame &frame)
	: m_data(NULL), m_w(0), m_h(0)
{
	*this = frame; // overloaded '=' is used
}


BYTE& Frame::operator()(int i, int j)
{
	return m_data[m_w * j + i];
}

BYTE* Frame::data()
{
	return m_data;
}

int Frame::width()
{
	return m_w;
}

int Frame::height()
{
	return m_h;
}

void Frame::adjustContrast(float ratio)
{
	for (int i = 0; i < m_w; i++)
		for (int j = 0; j < m_h; j++) {
			float value = m_data[m_w * j + i];
			value = (value - 128) * ratio + 128;

			if (ratio > 1.0)
				value = std::max((float) 0., std::min(value, (float) 255.));

			m_data[m_w * j + i] = value;
		}
}


void Frame::subSample(float ratio)
{
	sampleAlongX(ratio);
	sampleAlongY(ratio);
	//sharpen(12 * ratio);
}

void Frame::loadFromBMP(std::string filename)
{
	std::ifstream file(filename, std::ios::binary);

	if (!file.is_open()) {
		std::cerr << " Unable to open '" << filename << "'" << std::endl;
		throw std::exception();
	}

	int header_size = 54;

	char* header = new char[header_size];

	file.seekg(0, std::ios::beg);
	file.read(header, header_size);

	int width, height;

	BYTE lc, rc;

	lc = header[18];
	rc = header[19];
	width = ((int) lc) + 256 * ((int) rc);

	lc = header[22];
	rc = header[23];
	height = ((int) lc) + 256 * ((int) rc);

	m_w = width;
	m_h = height;

	lc = header[30];
	rc = header[31];
	int compression = ((int) lc) + 256 * ((int) rc);

	if (compression != 0) {
		std::cerr << " Only uncompressed BMPs are supported" << std::endl;
		throw std::exception();
	}

	lc = header[28];
	rc = header[29];
	int bpp = ((int) lc) + 256 * ((int) rc);

	if (bpp != 24) {
		std::cerr << " Only 24bit RGB images are supported" << std::endl;
		throw std::exception();
	}

	lc = header[10];
	rc = header[11];
	int offset = ((int) lc) + 256 * ((int) rc);

	file.seekg(offset, std::ios::beg);      // optional

	int row_size = std::ceil(((float) bpp * width) / 32) * 4;

	char * raw_data = new char[row_size * height];

	file.read(raw_data, row_size * height);

	//delete [] m_data;
	//m_data = new BYTE[width * height];

	BYTE * temp = m_data;
	m_data = new BYTE[width * height];
	delete [] temp;

	for (int i = 0 ; i < width; i++)
		for (int j = 0; j < height; j++) {
			m_data[j * width + i] = 0;

			for (int c = 0; c < 3; c++) {
				BYTE value = raw_data[(height - j - 1) * row_size + 3 * i + c];
				m_data[j * width + i] += (value / 3);
			}
		}

	delete [] header;
	delete [] raw_data;

	//std::cout << "width:    " << width << "\nheight:   " << height << "\ncpr:       "
	//	      << compression << "\nbpp:      " << bpp << "\noffset:   "
	//	      << offset << "\nrow size: " << row_size << std::endl;
}

Frame::~Frame()
{
	delete [] m_data;
}

}

