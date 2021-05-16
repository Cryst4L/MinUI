#include "Slider.h"

namespace MinUI
{

Slider::Slider(std::string id, Vector2f position, float width, Vector2f range)
	: m_id(id), m_position(position), m_dimension({width, 1}),
	m_range(range), m_midpoint({0, 0}), m_cursor_size({0, 0}), m_value(0.5)
{}

Slider* Slider::clone()
{
	return new Slider(*this);
}

void Slider::render(X11Context& context, Font& font)
{
	float height = 0.4;

	Vector2f position, dimension;

	position.x = (m_midpoint.x - 0.5f * m_cursor_size.x) / GRID_SIZE;
	position.y = (m_midpoint.y - 0.5f * m_cursor_size.y) / GRID_SIZE;

	dimension.x = m_cursor_size.x / GRID_SIZE;
	dimension.y = m_cursor_size.y / GRID_SIZE;

	drawBox(position, dimension, COLOR_BASE, context, 0, 1);

	////////////////////////////////////////////////////////

	position  = {m_position.x, (1 - height) * 0.5f * m_dimension.y + m_position.y};
	dimension = {m_dimension.x, m_dimension.y * height};

	drawBox(position, dimension, COLOR_BASE, context);

	dimension.x *= (m_value - m_range.x) / (m_range.y - m_range.x);

	drawBox(position, dimension, COLOR_FILL, context);

	////////////////////////////////////////////////////////
/*
	Vector2f offset = {0, (m_dimension.y * height) - 1.f / GRID_SIZE}; 

	position.x = position.x + dimension.x - m_dimension.y * 0.5f * height;
	position.y = position.y - 0.5f * height + 1 / GRID_SIZE;

	drawLine(position, add(position, offset), context, 1 , mix(COLOR_FILL, COLOR_OUTLINE));

	position.x += (m_cursor_size.x + 2.f) / GRID_SIZE;

	drawLine(position, add(position, offset), context, 1, COLOR_SHADOW);
*/
	position.x = (m_midpoint.x - 0.5f * m_cursor_size.x - 1) / GRID_SIZE;
	position.y = (m_midpoint.y - 0.5f * height * GRID_SIZE + 1) / GRID_SIZE;

	dimension.x = 0.5 * (m_cursor_size.x + 2) / GRID_SIZE;
	dimension.y = height - 1.f / GRID_SIZE;

	drawBox(position, dimension, mix(COLOR_FILL, COLOR_OUTLINE), context, 0, 0);

	position.x += 0.5 * (m_cursor_size.x + 4) / GRID_SIZE;

	drawBox(position, dimension, COLOR_SHADOW, context, 0, 0);

	////////////////////////////////////////////////////////

	position.x = (m_midpoint.x - 0.5f * m_cursor_size.x) / GRID_SIZE;
	position.y = (m_midpoint.y - 0.5f * m_cursor_size.y) / GRID_SIZE;

	dimension.x = m_cursor_size.x / GRID_SIZE;
	dimension.y = m_cursor_size.y / GRID_SIZE;

	Color c = m_focused ? COLOR_HOVER : COLOR_BUTTON;

	drawBox(position, dimension, c, context, 1, 0);

}

void Slider::update(InputState& input_state)
{
	float offset = (m_value - m_range.x) / (m_range.y - m_range.x);

	m_midpoint.x = (m_position.x + offset * m_dimension.x) * GRID_SIZE;
	m_midpoint.y = (m_position.y + 0.5 * m_dimension.y) * GRID_SIZE;

	m_cursor_size.x = 8;
	m_cursor_size.y = 0.6 * m_dimension.y * GRID_SIZE;

	bool b_l = input_state.mouse.x > (m_midpoint.x) - (8.0f * m_cursor_size.x);
	bool b_r = input_state.mouse.x < (m_midpoint.x) + (8.0f * m_cursor_size.x);
	bool b_u = input_state.mouse.y > (m_midpoint.y) - (0.5f * m_cursor_size.y);
	bool b_d = input_state.mouse.y < (m_midpoint.y) + (0.5f * m_cursor_size.y);

	m_focused = b_l && b_r && b_u && b_d;

	m_grabbed = false;

	if (m_focused && input_state.mouse.pressed)
		m_grabbed = true;

	if (m_grabbed) {
		bool i_l = input_state.mouse.x >= (m_position.x * GRID_SIZE);
		bool i_r = input_state.mouse.x <= (m_position.x + m_dimension.x) * GRID_SIZE;

		if (i_l && i_r) {
			offset = (input_state.mouse.x - m_position.x * GRID_SIZE)
			          / (m_dimension.x * GRID_SIZE);
			m_value = offset * (m_range.y - m_range.x) + m_range.x; 
			m_midpoint.x = (m_position.x + offset * m_dimension.x) * GRID_SIZE;
		}

	}
}

std::string Slider::id()
{
	return m_id;
}

bool Slider::isGrabbed()
{
	return m_grabbed;
}

float& Slider::value()
{
	return m_value;
}

}

