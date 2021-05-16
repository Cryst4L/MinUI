#include "CheckBox.h"

namespace MinUI
{

CheckBox::CheckBox(std::string id, std::string text, Vector2f position)
	: m_id(id), m_position(position), m_text(text), m_value(false)
{}

CheckBox* CheckBox::clone()
{
	return new CheckBox(*this);
}

void CheckBox::render(X11Context& context, Font& font)
{
	Vector2i center;

	center.x = (int) (m_position.x * GRID_SIZE + 0.5 * GRID_SIZE);
	center.y = (int) (m_position.y * GRID_SIZE + 0.5 * GRID_SIZE);

	int radius = int (0.25 * GRID_SIZE);

	Vector2i offsets[5] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}, {-1, 0}};

	XPoint points[5];

	for (int i = 0; i < 5; i++) {
		points[i].x =  center.x + (short)(offsets[i].x * radius);
		points[i].y =  center.y + (short)(offsets[i].y * radius);
	}

	////////////////////////////////////////////////////////////////////////

	Color color = m_focused ? COLOR_HOVER : COLOR_BASE;

	XSetForeground(context.display_p, context.gc, codeFromColor(color));

	XFillPolygon(context.display_p, context.buffer, context.gc, points, 5, Convex, CoordModeOrigin);

	////////////////////////////////////////////////////////////////////////

	XSetLineAttributes(context.display_p, context.gc, 1, LineSolid, 0, 0);
	XSetForeground(context.display_p, context.gc, codeFromColor(COLOR_OUTLINE));

	XDrawLines(context.display_p, context.buffer, context.gc, points, 5, CoordModeOrigin);

	for (int i = 0; i < 5; i++) {
		points[i].x = (short) (points[i].x + offsets[i].x);
		points[i].y = (short) (points[i].y + offsets[i].y);
	}

	XDrawLines(context.display_p, context.buffer, context.gc, points, 5, CoordModeOrigin);

	////////////////////////////////////////////////////////////////////////

	if (m_value) {
		radius = int (0.20 * GRID_SIZE);

		for (int i = 0; i < 5; i++) {
			points[i].x = center.x + (short) (offsets[i].x * radius);
			points[i].y = center.y + (short) (offsets[i].y * radius);
		}

		XSetForeground(context.display_p, context.gc, codeFromColor(COLOR_FILL));
		XDrawLines(context.display_p, context.buffer, context.gc, points, 5, CoordModeOrigin);
		XFillPolygon(context.display_p, context.buffer, context.gc, points, 5, Convex, CoordModeOrigin);
	}

	////////////////////////////////////////////////////////////////////////

	Vector2f position = {m_position.x + 0.75f, m_position.y };

	font.colorScheme() = EMPHASIS;

	drawText(m_text, position, font, context);

}

void CheckBox::update(InputState& input_state)
{
	m_clicked = false;

	bool b_l = input_state.mouse.x > ((m_position.x) * GRID_SIZE);
	bool b_r = input_state.mouse.x < ((m_position.x + 1.0) * GRID_SIZE);
	bool b_u = input_state.mouse.y > ((m_position.y) * GRID_SIZE);
	bool b_d = input_state.mouse.y < ((m_position.y + 1.0) * GRID_SIZE);

	m_focused = b_l && b_r && b_u && b_d;

	if (m_focused && input_state.mouse.clicked) {
		m_value = (1 - m_value);
		m_clicked = 1;
	}
}


std::string CheckBox::id()
{
	return m_id;
}

bool& CheckBox::value()
{
	return m_value;
}

bool CheckBox::isClicked()
{
	return m_clicked;
}
}
