////////////////////////////////////////////////////////////////////////////////
// Slider.h
// -----------------------------------------------------------------------------
// Implements the widget 'Slider'. 
// User can retreive or update the slider's position using the method 'value()'.
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Widget.h"

namespace MinUI
{
class Slider : public Widget
{
    private :
	std::string m_id;

	Vector2f m_position;
	Vector2f m_dimension;

	Vector2f m_range;

	Vector2f m_midpoint;
	Vector2f m_cursor_size;

	float m_value;

	bool m_focused;
	bool m_grabbed;
	bool m_new_value;

    public :

	Slider(std::string id, Vector2f position, float width, Vector2f range);

	Slider* clone();

	std::string id();

	////////////////////////////////////////////////////////////////////////////

	void render(X11Context& context, Font& font);

	void update(InputState& input_state);

	////////////////////////////////////////////////////////////////////////////

	bool isGrabbed();

	float& value();
};

}

