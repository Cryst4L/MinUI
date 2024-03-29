#include "Canvas.h"
#include "Container.h"

namespace MinUI
{

/*
bool checkBoundaries(Vector2f position, Vector2f dimension)
{
	bool valid = (position.x + dimension.x) < m_dimension.x &&
		         (position.y + dimension.y) < m_dimension.y;

	if (!valid)
		std::cerr << "Widget placed out of canvas boundaries." << std::endl;

	return valid;
}
*/

void Canvas::renderSelf(X11Context& context, Font& font)
{
	Color background = m_parity ? COLOR_BASE : COLOR_EMPHASIS;

	Vector2f position = add(m_position, m_canvas_padding);
	Vector2f dimension = add(m_dimension, {0., 1.});

	bool outline = (m_style != NOBORDER);

	if (m_title != "") {
		position = add(position, {0., -0.5});
		dimension = add(dimension, {0., 0.5});// {0., -0.5});
	}

	drawBox(position, dimension, background, context, outline);

	if (m_title != "") {
		font.colorScheme() = m_parity ? BASE : EMPHASIS;

		position = add(position, {1, -0.5});

		drawHeader(m_title, position, font, context, m_parity);
	}
}

Canvas::Canvas() {}

Canvas::Canvas(std::string id, Vector2f position, Vector2f dimension,
             std::string title, BorderEnum style, bool parity)
	: m_id(id), m_position(position), m_dimension(dimension),
	  m_title(title), m_style(style), m_parity(parity)
{
	m_canvas_padding = {0., 0.};
	m_widget_padding  = {.5f, .5f};

	if (m_style == MARGIN) {
		m_canvas_padding   = {.5f, .5f};
		m_widget_padding  = {1.f, 1.f};
	}

	if (m_title != "") {
		m_canvas_padding.y  += 1.0f;
		m_widget_padding.y += 1.0f;
	}
}

Canvas::~Canvas() {}

////////////////////////////////////////////////////////////////////////////

std::string Canvas::id()
{
	return m_id;
}

Canvas& Canvas::canvas(int index)
{
	return m_childs[index];
}

std::vector <Canvas> & Canvas::childs()
{
	return m_childs;
}

void Canvas::resize(float width, float height)
{
	m_dimension = {width, height};
}

Container& Canvas::container()
{
	return m_container;
}

////////////////////////////////////////////////////////////////////////////

void Canvas::render(X11Context& context, Font& font)
{
	renderSelf(context, font);

	m_container.render(context, font);

	for (int i = 0; i < (int) m_childs.size(); i++)
		m_childs[i].render(context, font);

}

void Canvas::update(InputState& input_state)
{
	m_container.update(input_state);

	for (int i = 0; i < (int) m_childs.size(); i++)
		m_childs[i].update(input_state);
}

void Canvas::addCanvas(std::string id, Vector2f position, Vector2f dimension,
                     std::string title, BorderEnum style)
{
	position = add(add(m_position, position), m_canvas_padding);
	Canvas canvas(id, position, dimension, title, style, !m_parity);
	m_childs.push_back(canvas);
}

void Canvas::addLabel(std::string id, std::string label, Vector2f position)
{
	position = add(add(m_position, position), m_widget_padding);
	m_container.addLabel(id, label, position);
}

void Canvas::addButton(std::string id, std::string text, Vector2f position, Vector2f dimension)
{
	position = add(add(m_position, position), m_widget_padding);
	m_container.addButton(id, text, position, dimension);
}

void Canvas::addSlider(std::string id, Vector2f position, float width, Vector2f range)
{
	position = add(add(m_position, position), m_widget_padding);
	m_container.addSlider(id, position, width, range);
}

void Canvas::addEntry(std::string id, Vector2f position, float width, bool numeric)
{
	position = add(add(m_position, position), m_widget_padding);
	m_container.addEntry(id, position, width, numeric);
}

void Canvas::addCheckBox(std::string id, std::string text, Vector2f position)
{
	position = add(add(m_position, position), m_widget_padding);
	m_container.addCheckBox(id, text, position);
}

void Canvas::addTrackBar(std::string id, Vector2f position, float width)
{
	position = add(add(m_position, position), m_widget_padding);
	m_container.addTrackBar(id, position, width);
}

void Canvas::addImage(std::string id, Vector2f position, std::string path)
{
	position = add(add(m_position, position), m_widget_padding);
	m_container.addImage(id, position, path);
}

void Canvas::addImage(std::string id, Vector2f position, Vector2i size, BYTE* data)
{
	position = add(add(m_position, position), m_widget_padding);
	m_container.addImage(id, position, size, data);
}

}



