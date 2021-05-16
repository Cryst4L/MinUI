////////////////////////////////////////////////////////////////////////////////
// Draw.h
// -----------------------------------------------------------------------------
// Implements a dynamically allocated 2D array of bytes that can be loaded from
// a BMP. Is used in the implementation of the Fonts.
// Note that a Frame is not a widget. For an image widget see 'Image.h'.
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cmath>
#include <fstream>
#include <string>
#include <iomanip>
#include <exception>
#include <iostream>

#include "Types.h"

namespace MinUI
{
class Frame
{
    private:

	BYTE * m_data;
	int m_w, m_h;

	void sampleAlongX(float ratio);
	void sampleAlongY(float ratio);

    public :

	Frame();

	Frame(int width, int height);

	Frame& operator=(const Frame &frame);

	Frame(const Frame &frame);

	~Frame();

	////////////////////////////////////////////////////////////////////////////

	BYTE& operator()(int i, int j);

	BYTE* data();

	int width();

	int height();

	void adjustContrast(float ratio);

	void subSample(float ratio);

	////////////////////////////////////////////////////////////////////////////

	void loadFromBMP(std::string filename);

};
}

