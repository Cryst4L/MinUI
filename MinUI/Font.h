////////////////////////////////////////////////////////////////////////////////
// Font.h
// -----------------------------------------------------------------------------
// Implements the text fonts. 
// Fonts are loaded from a BMP character sheet into vectors of Pixmaps, which 
// are textures stored in the server side.
// When a font is loaded, the glyphs are internaly rendered according to every 
// one of the default color schemes (see 'Style.h'). 
// Once loading is done, the user can select the color scheme to be used using 
// the 'setColorScheme()' method, and retreive the glyphs using the method 
// 'Pixmaps()'.
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Widget.h"
#include "Inputs.h"
#include "Types.h"
#include "Frame.h"
#include "Style.h"

#include <vector>
#include <cstring>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

//TODO add a XFreePixmap

namespace MinUI
{
class Font
{
    private :

	typedef std::vector<Pixmap> Table;

	Frame m_charset;

	float m_font_size;

	int m_font_width;
	int m_font_height;

	std::vector <Table> m_pixmaps;

	ColorSchemeEnum m_color_scheme;

	void buildPixmaps(X11Context& context, float font_size);

	void init(std::string path, float font_size, X11Context& context);

    public :

	Font();

	Font(std::string path, float font_size, X11Context& context);

	ColorSchemeEnum& colorScheme();

	std::vector <Pixmap> pixmaps(); // TODO use an enum here

	int width();
	int height();

};
}

