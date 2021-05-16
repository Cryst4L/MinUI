////////////////////////////////////////////////////////////////////////////////
// CheckBox.h
// -----------------------------------------------------------------------------
// Implements the widget 'CheckBox'. User can retreive the checkbox state using 
// the  method 'value()'.
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Widget.h"
#include "Types.h"
#include "Utils.h"
#include "Draw.h"
#include "Inputs.h"

#include <iomanip>
#include <string>

namespace MinUI
{
class CheckBox : public Widget
{
    private:

	std::string m_id;

	Vector2f m_position;

	std::string m_text;

	bool m_value;
	bool m_focused;
	bool m_clicked;

    public:

	CheckBox(std::string id, std::string text, Vector2f position);

	CheckBox* clone();

	std::string id();

	////////////////////////////////////////////////////////////////////////////

	void render(X11Context& context, Font& font);

	void update(InputState& input_state);

	////////////////////////////////////////////////////////////////////////////

	bool& value();

	bool isClicked();
};

}
