////////////////////////////////////////////////////////////////////////////////
// Button.h
// -----------------------------------------------------------------------------
// Implements the widget 'Button'. User can retreive the button state using the
// method 'clicked()'.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Widget.h"
#include "Draw.h"
#include "Types.h"
#include <iomanip>
#include "Utils.h"

namespace MinUI
{
class Button : public Widget
{
    private:

	std::string m_id;

	Vector2f m_position;
	Vector2f m_dimension;

	std::string m_text;

	bool m_focused;
	bool m_clicked;
	bool m_pressed;

    public:

	Button();

	Button(std::string id, std::string text, Vector2f position, Vector2f dimension);

	Button* clone();

	void render(X11Context& context, Font& font);

	void update(InputState& input_state);

	std::string id();

	bool isClicked();
};

}

