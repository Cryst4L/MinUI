////////////////////////////////////////////////////////////////////////////////
// TrackBar.h
// -----------------------------------------------------------------------------
// Implements the widget 'TrackBar'.
// User can get and set the value of the trackbar using the method 'value()'. 
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Widget.h"
#include "Draw.h"
#include "Types.h"
#include "Utils.h"

#include <iomanip>

namespace MinUI
{
class TrackBar : public Widget
{
    private :

	std::string m_id;

	Vector2f m_position;
	Vector2f m_dimension;

	float m_value;

    public :

	TrackBar(std::string id, Vector2f position, float width);

	TrackBar* clone();

	void update(InputState& input_state);

	void render(X11Context& context, Font& font);

	std::string id();
};
}

