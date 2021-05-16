#include "TrackBar.h"

namespace MinUI
{

TrackBar::TrackBar(std::string id, Vector2f position, float width)
	: m_id(id), m_position(position), m_dimension({width, 1}), m_value(0.5)
{}

TrackBar* TrackBar::clone()
{
	return new TrackBar(*this);
}

void TrackBar::update(InputState& input_state) {}

void TrackBar::render(X11Context& context, Font& font)
{
	Vector2f position;

	position.x = m_position.x;
	position.y = m_position.y + 0.5 * (m_dimension.y - 0.5);

	Vector2f dimension;

	dimension.x = m_dimension.x;
	dimension.y = 0.5;

	drawBox(position, dimension, COLOR_BASE, context);

	dimension.x *= m_value;

	drawBox(position, dimension, COLOR_FILL, context, 0, 0);

	dimension.x = m_dimension.x;

	XSetForeground(context.display_p, context.gc, codeFromColor(COLOR_OUTLINE));

	XDrawRectangle(context.display_p, context.buffer, context.gc,
	               position.x * GRID_SIZE, position.y * GRID_SIZE,
	               dimension.x * GRID_SIZE, dimension.y * GRID_SIZE);

}

std::string TrackBar::id()
{
	return m_id;
}

}

