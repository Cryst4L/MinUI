#include "Draw.h"

namespace MinUI
{

void drawLine(Vector2f a, Vector2f b, X11Context& context, int width, Color color)
{
	XSetLineAttributes(context.display_p, context.gc, width, LineSolid, 0, 0);

	XSetForeground(context.display_p, context.gc, codeFromColor(color));

	XDrawLine(context.display_p, context.buffer, context.gc, a.x * GRID_SIZE,
	          a.y * GRID_SIZE, b.x * GRID_SIZE, b.y * GRID_SIZE);
}


void drawBox(Vector2f position, Vector2f dimension,
             Color fill_color, X11Context& context, bool outline, bool shadow)
{
	if (shadow) {
		XSetLineAttributes(context.display_p, context.gc, 3, LineSolid, 0, 0);

		XSetForeground(context.display_p, context.gc, codeFromColor(COLOR_SHADOW));

		XDrawRectangle(context.display_p, context.buffer, context.gc,
		               position.x * GRID_SIZE, position.y * GRID_SIZE,
		               dimension.x * GRID_SIZE, dimension.y * GRID_SIZE);
	}

	////////////////////////////////////////////////////////////////////////

	XSetForeground(context.display_p, context.gc, codeFromColor(fill_color));

	XFillRectangle(context.display_p, context.buffer, context.gc,
	               position.x * GRID_SIZE, position.y * GRID_SIZE,
	               dimension.x * GRID_SIZE, dimension.y * GRID_SIZE);

	////////////////////////////////////////////////////////////////////////

	if (outline) {
		XSetLineAttributes(context.display_p, context.gc, 1, LineSolid, 0, 0);

		XSetForeground(context.display_p, context.gc, codeFromColor(COLOR_OUTLINE));

		XDrawRectangle(context.display_p, context.buffer, context.gc,
		               position.x * GRID_SIZE, position.y * GRID_SIZE,
		               dimension.x * GRID_SIZE, dimension.y * GRID_SIZE);
	}

}

void drawText(std::string text, const Vector2f position,
              Font& font, X11Context& context, bool padded)
{

	int l = 0;

	while (text[l] != '\0')
		l++;

	int char_w = font.width();
	int char_h = font.height();

	Vector2i padding = {0, 0};

	if (padded) {
		padding.x = (int) (0.25 * (GRID_SIZE - char_w));
		padding.y =	(int) (0.5 * (GRID_SIZE - char_h));
	}

	Vector2i offset = {(int) (padding.x + position.x * GRID_SIZE),
	                   (int) (padding.y + position.y * GRID_SIZE)
	                  };

	std::vector <Pixmap> pixmaps = font.pixmaps();

	for (int i = 0; i < l; i++) {
		BYTE c = (BYTE) text[i];

		if (c >= 32 && c < 128) 
		{
			Pixmap pixmap = pixmaps[c - 32];

			XCopyArea(context.display_p, pixmap, context.buffer, context.gc,
			          0, 0, char_w, char_h, offset.x, offset.y);

			offset.x += char_w;
		}

		if (c == '\n') {
			offset.x = padding.x + position.x * GRID_SIZE;
			offset.y += GRID_SIZE;
		}
	}

	//XFlush(context.display_p);
}

void drawHeader(std::string title, Vector2f position, Font& font, X11Context& context, bool parity)
{
	int pad = 0.5 * GRID_SIZE;
	int width = (font.width() * (title.length() + 1));

	Vector2i vertices[7] = {{-pad, pad}, {0, 0}, {width, 0},  {width + pad, pad},
		{width, 2 * pad}, {0, 2 * pad}, {-pad, pad}
	};

	Vector2i offset = {(int) (position.x * GRID_SIZE), (int) (position.y * GRID_SIZE)};

	for (int i = 0; i < 7; i++)
		vertices[i] = add(vertices[i], offset);

	XPoint points[7];

	for (int i = 0; i < 7; i++)
		points[i] = {(short) vertices[i].x, (short) vertices[i].y};

	////////////////////////////////////////////////////////////////////////////

	Color fill_color = parity ? COLOR_BASE : COLOR_EMPHASIS;

	XSetForeground(context.display_p, context.gc, codeFromColor(fill_color));

	XFillPolygon(context.display_p, context.buffer, context.gc, points, 6, Convex, CoordModeOrigin);

	XSetLineAttributes(context.display_p, context.gc, 1, LineSolid, 0, 0);

	XSetForeground(context.display_p, context.gc, codeFromColor(COLOR_OUTLINE));

	XDrawLines(context.display_p, context.buffer, context.gc, points, 7, CoordModeOrigin);


	////////////////////////////////////////////////////////////////////////////

	XPoint offsets[7] = {{-1, 0}, {0, -1}, {0, -1}, {1, 0}, {0, 1}, {0, 1}, {-1, 0}};

	for (int i = 0; i < 7; i++)
		points[i] = {(short) (points[i].x + offsets[i].x), (short) (points[i].y + offsets[i].y)};

	//XSetForeground(context.display_p, context.gc, codeFromColor(COLOR_SHADOW));
	XDrawLines(context.display_p, context.buffer, context.gc, points, 7, CoordModeOrigin);

	///////////////////////////////////////////////////////////////////////////////////////////////

	XSetForeground(context.display_p, context.gc, codeFromColor(COLOR_SHADOW));

	XPoint line[2];

	line[0] = points[1];

	line[1] = points[2];

	XDrawLines(context.display_p, context.buffer, context.gc, line, 2, CoordModeOrigin);

	line[0] = points[4];

	line[1] = points[5];

	XDrawLines(context.display_p, context.buffer, context.gc, line, 2, CoordModeOrigin);

	///////////////////////////////////////////////////////////////////////////////////////////////

	font.colorScheme() = parity ? BASE : EMPHASIS;

	drawText(title, position, font, context);
}


}
