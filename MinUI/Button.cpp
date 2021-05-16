#include "Button.h"

namespace MinUI
{

Button::Button() {};

Button::Button(std::string id, std::string text, Vector2f position, Vector2f dimension)
	: m_id(id), m_position(position), m_dimension(dimension), m_text(text),
	  m_focused(false), m_clicked(false), m_pressed(false)
{}

Button* Button::clone()
{
	return new Button(*this);
}

void Button::render(X11Context& context, Font& font)
{
	Color fill_color =  m_focused ? COLOR_HOVER : COLOR_BUTTON;

	float margin = 0.2;

	Vector2f position, dimension;

	position = add(m_position, {0.5f * margin, 0.5f * margin});

	dimension = add(m_dimension, {- margin, - margin});

	drawBox(position, dimension, fill_color, context);

	Vector2f offset;

	offset.x = ((dimension.x * GRID_SIZE - m_text.length() * font.width()) * 0.5) / GRID_SIZE;
	offset.y = (dimension.y * GRID_SIZE - font.height()) * 0.5 / GRID_SIZE;

	Vector2f centered = { position.x + offset.x, position.y + offset.y};

	font.colorScheme() = m_focused ? HOVER : BUTTON;

	drawText(m_text, centered, font, context, 0);
}

void Button::update(InputState& input_state)
{
	bool b_l = input_state.mouse.x > (m_position.x * GRID_SIZE);
	bool b_r = input_state.mouse.x < (m_position.x + m_dimension.x) * GRID_SIZE;
	bool b_u = input_state.mouse.y > (m_position.y * GRID_SIZE);
	bool b_d = input_state.mouse.y < (m_position.y + m_dimension.y) * GRID_SIZE;

	m_focused = b_l && b_r && b_u && b_d;

	m_pressed = m_focused && input_state.mouse.pressed;
	m_clicked = m_focused && input_state.mouse.clicked;
}

std::string Button::id()
{
	return m_id;
}

bool Button::isClicked()
{
	return m_clicked;
}

}


