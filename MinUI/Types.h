////////////////////////////////////////////////////////////////////////////////
// Types.h
// -----------------------------------------------------------------------------
// Implements custom types.
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <X11/Xlib.h>
#include <X11/Xutil.h>

namespace MinUI
{
typedef unsigned char BYTE;

typedef struct {
	int x, y;
} Vector2i;

typedef struct {
	float x, y;
} Vector2f;

typedef struct {
	BYTE r, g, b;
} Color;

typedef struct {
	Display * display_p;
	XVisualInfo info;
	Window window;
	Pixmap buffer;
	GC gc;
} X11Context;
}
