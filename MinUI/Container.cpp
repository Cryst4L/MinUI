#include "Container.h"
#include "Canvas.h"

namespace MinUI
{
Container::Container() {}

Container::Container(const Container &container)
{
	*this = container;
}

Container& Container::operator=(const Container &container)
{
	if (this != &container) 
	{
		//TODO: delete the widgets before calling clear
		m_widgets.clear();
		for (int i = 0; i < (int) container.m_widgets.size(); i++) {
			//widget = new Widget(container.m_widgets[i]);
			Widget * widget = container.m_widgets[i]->clone();
			m_widgets.push_back(widget);
		}
	}

	return *this;
}

Container::~Container()
{
	for (int i = 0; i < (int) m_widgets.size(); i++)
		delete m_widgets[i];
}


void Container::update(InputState& input_state)
{
	for (int i = 0; i < (int) m_widgets.size(); i++)
		m_widgets[i]->update(input_state);
}

void Container::render(X11Context& context, Font& font)
{
	for (int i = 0; i < (int) m_widgets.size(); i++)
		m_widgets[i]->render(context, font);
}

void Container::addLabel(std::string id, std::string text, Vector2f position)
{
	Label* label = new Label(id, text, position);
	m_widgets.push_back(label);
}

void Container::addButton(std::string id, std::string label, Vector2f position, Vector2f dimension)
{
	Button* button = new Button(id, label, position, dimension);
	m_widgets.push_back(button);
}

void Container::addSlider(std::string id, Vector2f position, float width, Vector2f range)
{
	Slider* slider = new Slider(id, position, width, range);
	m_widgets.push_back(slider);
}

void Container::addEntry(std::string id, Vector2f position, float width, bool numeric)
{
	Entry* entry = new Entry(id, position, width, numeric);
	m_widgets.push_back(entry);
}

void Container::addCheckBox(std::string id, std::string text, Vector2f position)
{

	CheckBox* checker = new CheckBox(id, text, position);
	m_widgets.push_back(checker);

}

void Container::addTrackBar(std::string id, Vector2f position, float width)
{
	TrackBar* track_bar = new TrackBar(id, position, width);
	m_widgets.push_back(track_bar);
}

void Container::addImage(std::string id, Vector2f position, std::string path)
{
	Image* image = new Image(id, position, path);
	m_widgets.push_back(image);
}

void Container::addImage(std::string id, Vector2f position, Vector2i size, BYTE* data)
{
	Image* image = new Image(id, position, size, data);
	m_widgets.push_back(image);
}

Widget& Container::widget(int i)
{
	return *m_widgets[i];
}

int Container::size()
{
	return m_widgets.size();
}

}

