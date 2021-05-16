////////////////////////////////////////////////////////////////////////////////
// Image.h
// -----------------------------------------------------------------------------
// Implements the widget 'Image'. 
// The image is stored in a dynamically allocated array where RGB values are 
// placed contiguously. 
// The Image can be loaded from a BMP file (24bpp), or from a data pointer. 
// In case the data changes, the user can update the image using the method 
// 'setData()' .
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Types.h"
#include "Widget.h"

#include <string>
#include <cstdlib>
#include <exception>

namespace MinUI
{
class Image : public Widget
{
    private :

	std::string m_id;

	Vector2f m_position;

	Vector2i m_size;

	BYTE * m_data_p;

	XImage * m_image_p;

	X11Context m_context;

	bool m_setup;

	void reallocate(int width, int height);

    public :

//	Image()

	Image(std::string id, Vector2f position, Vector2i size, BYTE* data);

	Image(std::string id, Vector2f position, std::string path);

	Image(std::string id, Vector2f position, Vector2i size);

	Image& operator=(const Image &image);

	Image(const Image &image);

	Image * clone();

	std::string id();

	~Image();

	////////////////////////////////////////////////////////////////////////////

	void render(X11Context& context, Font& font);

	void update(InputState& input_state);

	////////////////////////////////////////////////////////////////////////////

	void setData(BYTE * raw_data, bool flip = 0);

	void loadFromData(BYTE * raw_data, int width, int height, bool flip = 0);

	void loadFromBMP(std::string filename);

};
}

