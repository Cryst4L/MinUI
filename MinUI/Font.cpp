#include "Font.h"

//TODO add a XFreePixmap

namespace MinUI
{
Font::Font() {}

void Font::init(std::string path, float font_size, X11Context& context)
{
	m_charset.loadFromBMP(path);
	m_color_scheme = BASE;
	buildPixmaps(context, font_size);
}

Font::Font(std::string path, float font_size, X11Context& context)
{
	init(path, font_size, context);
}

void Font::buildPixmaps(X11Context& context, float font_size)
{
	m_pixmaps.clear();

	float exact_char_w = m_charset.width() / 16.;
	float exact_char_h = m_charset.height() / 6.;

	int char_w = std::floor(exact_char_w);
	int char_h = std::floor(exact_char_h);

	std::vector <Frame> frames;

	for (int c = 0; c < 96; c++) {
		int offset_x = std::floor((c % 16) * exact_char_w);
		int offset_y = std::floor((c / 16) * exact_char_h);

		Frame character(char_w, char_h);

		for (int i = 0; i < char_w; i++)
			for (int j = 0; j < char_h; j++)
				character(i, j) = m_charset(offset_x + i, offset_y + j);

		frames.push_back(character);
	}

	float init_font_size = 0.5 * (exact_char_w + exact_char_h);
	float sampling_ratio = font_size / init_font_size;
	m_font_size = font_size;

	for (int c = 0; c < 96; c++)
		frames[c].subSample(sampling_ratio);


	char_w = frames[0].width();
	char_h = frames[0].height();

	m_font_width = char_w;
	m_font_height = char_h;

	Display * display_p = context.display_p;
	Pixmap buffer = context.buffer;
	XVisualInfo info = context.info;
	GC gc = context.gc;

	for (int s = 0; s < NB_COLOR_SCHEMES; s++) {
		Table pixmap_table;

		Color c_a = DEFAULT_COLOR_SCHEMES[s].background;
		Color c_b = DEFAULT_COLOR_SCHEMES[s].foreground;

		for (int c = 0; c < 96; c++) {
			char * padded_data = (char*) malloc(4 * char_w * char_h * sizeof(BYTE));

			for (int i = 0; i < char_w; i++)
				for (int j = 0; j < char_h; j++) {
					float value = frames[c](i, j) / 256.;

					// TODO: implement a color class
					int r = c_a.r * value + c_b.r * (1 - value);
					int g = c_a.g * value + c_b.g * (1 - value);
					int b = c_a.b * value + c_b.b * (1 - value);

					int position = (char_w * j + i);

					padded_data[4 * position]     = b;
					padded_data[4 * position + 1] = g;
					padded_data[4 * position + 2] = r;
					padded_data[4 * position + 3] = 0;
				}

			XImage * image_p = XCreateImage(display_p, info.visual, 24, ZPixmap,
			                                0, padded_data, char_w, char_h, 8, 0);

			Pixmap pixmap = XCreatePixmap(display_p, buffer, char_w, char_h, info.depth);

			XPutImage(display_p, pixmap, gc, image_p, 0, 0, 0, 0, char_w, char_h);

			pixmap_table.push_back(pixmap);

			XDestroyImage(image_p);
		}

		m_pixmaps.push_back(pixmap_table);
	}
}

ColorSchemeEnum& Font::colorScheme()
{
	return m_color_scheme;
}

std::vector <Pixmap> Font::pixmaps() // TODO use an enum here
{
	return m_pixmaps[m_color_scheme];
}

int Font::width()
{
	return m_font_width;
}

int Font::height()
{
	return m_font_height;
}

}

