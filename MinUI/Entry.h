////////////////////////////////////////////////////////////////////////////////
// Entry.h
// ----------------------------------------------------------------------------
// Implements the widget 'Entry'. An entry can either be used to enter text or 
// numeric values. In the first case user can retreive the string using the
// method 'text()', in the later the user can retreive the numeric value using
// the method 'value()'.  
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Widget.h"
#include "Timer.h"

namespace MinUI
{

class Entry : public Widget
{
    private :

	std::string m_id;

	Vector2f m_position;
	Vector2f m_dimension;

	std::string m_string;

	Vector2i m_font_size;

	Timer m_timer;

	float m_value;

	bool m_numeric;
	bool m_focused;
	bool m_locked;

	bool m_new_entry;
	bool m_new_value;

	bool numericFilter(unsigned int symbol);
	bool textFilter(unsigned int symbol);

    public :

	Entry(std::string id, Vector2f position, float width, bool numeric = false);

	Entry * clone() ;

	std::string id();

	void update(InputState& input_state);

	void render(X11Context& context, Font& font);

	float& value();

	bool newEntry();
};

}


