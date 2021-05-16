////////////////////////////////////////////////////////////////////////////////
// Label.h
// -----------------------------------------------------------------------------
// Implements the widget 'Label'.
// A label consists of a simple string of text. 
// The user can update the string content using the method 'text()'.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Widget.h"
#include "Font.h"

namespace MinUI
{
class Label : public Widget
{
    private :

	std::string m_id;

	Vector2f m_position;

	std::string m_text;

    public :

	Label(std::string id, std::string text, Vector2f position);

	Label* clone();

	std::string id();

	void render(X11Context& context, Font& font);

	void update(InputState& input_state);

};
}


