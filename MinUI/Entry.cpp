#include "Entry.h"

namespace MinUI
{

bool Entry::numericFilter(unsigned int symbol)
{
	bool valid = (symbol > 47 && symbol < 58);

	if (symbol == 45) {
		valid |= m_string.empty();
	} else if (symbol == 46) {
		valid |= (m_string.find('.') == std::string::npos);
	}

	return valid;
}

bool Entry::textFilter(unsigned int symbol)
{
	bool valid = (symbol == 95);
	valid |= (symbol > 44 && symbol < 47);
	valid |= (symbol > 47 && symbol < 58);
	valid |= (symbol > 64 && symbol < 91);
	valid |= (symbol > 96 && symbol < 123);
	return valid;
}



Entry::Entry(std::string id, Vector2f position, float width, bool numeric)
	: m_id(id), m_position(position), m_dimension({width, 1}), m_string(""),
m_value(0), m_numeric(numeric), m_locked(0), m_new_entry(0), m_new_value(1)
{}

Entry * Entry::clone()
{
	return new Entry(*this);
}

void Entry::update(InputState& input_state)
{
	bool b_l = input_state.mouse.x > m_position.x * GRID_SIZE;
	bool b_r = input_state.mouse.x < (m_position.x + m_dimension.x) * GRID_SIZE;
	bool b_u = input_state.mouse.y > m_position.y * GRID_SIZE;
	bool b_d = input_state.mouse.y < (m_position.y + m_dimension.y) * GRID_SIZE;

	m_focused = b_l & b_r & b_u & b_d;

	bool pre_locked = m_locked;

	if (m_locked && input_state.mouse.clicked && !m_focused)
		m_locked = false;

	if (m_focused && input_state.mouse.clicked)
		m_locked = true;

	if (m_locked && input_state.keyboard.stroke) {
		unsigned int symbol = input_state.keyboard.symbol;

		if (symbol == XK_BackSpace && m_string.size() != 0) {
			m_string.erase(m_string.end() - 1);
		} else if (symbol == XK_Return) {
			m_locked = false;
		} else if ((m_string.length() * m_font_size.x) < ((m_dimension.x - 0.25) * GRID_SIZE)) {
			bool valid = m_numeric ? numericFilter(symbol) : textFilter(symbol);

			if (valid) {
				m_string += static_cast <char> (symbol);
			}
		}

		/*
		if (symbol == XK_Shift_L || symbol == XK_Shift_R) {
			m_caps
		}
		*/


	}

	//////////////////////////////////////////////////////////////////////////////
/*
	std::ostringstream ostr;
	ostr << std::setprecision(4) << m_value;
	m_string = ostr.str();
*/
	m_new_entry = pre_locked && !m_locked;

	if (m_new_entry)
		m_value = m_numeric ? std::atof(m_string.c_str()) : 0.f;

	if (m_new_value) {
		std::ostringstream ostr;
		ostr << std::setprecision(m_dimension.x) << m_value;
		m_string = ostr.str();
		m_new_value = false;
	}
}

void Entry::render(X11Context& context, Font& font)
{
	m_font_size.x = font.width();
	m_font_size.y = font.height();

	//Color color = COLOR_BASE;
	Color color = m_locked ? COLOR_FILL : COLOR_BASE;

	Vector2f position, dimension;

	position.x = m_position.x;
	position.y = m_position.y + (m_dimension.y - (m_font_size.y / (float) GRID_SIZE)) * 0.5f;

	dimension.x = m_dimension.x;
	dimension.y = m_font_size.y / (float) GRID_SIZE;

	float e = 2.0 / GRID_SIZE;

	drawBox(add(position, {-e, -e}), add(dimension, {2 * e, 2 * e}), color, context);

	font.colorScheme() = m_locked ? FILL : BASE;

	drawText(m_string, position, font, context, 0);

	//////////////////////////////////////////////////////////////////////////////

	bool parity = ((int) m_timer.getTimeMS() / 500) % 2;

	if (m_locked && parity) {
		color = m_locked ? COLOR_INVERTED : COLOR_TEXT;

		XSetForeground(context.display_p, context.gc, codeFromColor(color));

		Vector2f padding;

		padding.x = -0.2 * (GRID_SIZE - font.width());
		padding.y =  0.9 * (GRID_SIZE - font.height());

		position.x = m_position.x * GRID_SIZE + m_font_size.x * (m_string.length() + 1);
		position.y = m_position.y * GRID_SIZE;

		position = add(position, padding);

		XFillRectangle(context.display_p, context.buffer, context.gc,
		               position.x, position.y, 2, FONT_SIZE);
	}

}

std::string Entry::id()
{
	return m_id;
}


float& Entry::value()
{
	m_new_value = true;
	return m_value;
}


bool Entry::newEntry()
{
	return m_new_entry;
}

}


