#include "Label.h"

namespace MinUI
{

Label::Label(std::string id, std::string text, Vector2f position)
	: m_id(id), m_position(position), m_text(text)
{}

Label* Label::clone()
{
	return new Label(*this);
}

void Label::render(X11Context& context, Font& font)
{
	font.colorScheme() = EMPHASIS;
	drawText(m_text, m_position, font, context);
}

void Label::update(InputState& input_state) {}

std::string Label::id()
{
	return m_id;
}

}


