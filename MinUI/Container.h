////////////////////////////////////////////////////////////////////////////////
// Container.h
// -----------------------------------------------------------------------------
// A container is a storage element for the widgets. 
// Each canvas holds a container fot it's affiliated widgets. 
// Inside a container, widgets are stored in a polymorphic fashion (that is to 
// say using pointers of base class 'Widget').
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Label.h"
#include "Button.h"
#include "Slider.h"
#include "Entry.h"
#include "CheckBox.h"
#include "TrackBar.h"
#include "Image.h"

//#include "Canvas.h"

#include <string>

namespace MinUI
{

class Canvas; //circular dependency

class Container
{
    private:

	std::vector <Widget*> m_widgets;

    public:

	Container();

	Container(const Container &container);

	Container& operator=(const Container &container);

	~Container();

	////////////////////////////////////////////////////////////////////////////

	void update(InputState& input_state);

	void render(X11Context& context, Font& font);

	////////////////////////////////////////////////////////////////////////////

	void addLabel(std::string id, std::string text, Vector2f position);

	void addButton(std::string id, std::string label, Vector2f position, Vector2f dimension);

	void addSlider(std::string id, Vector2f position, float width, Vector2f range);

	void addEntry(std::string id, Vector2f position, float width, bool numeric);

	void addCheckBox(std::string id, std::string text, Vector2f position);

	void addTrackBar(std::string id, Vector2f position, float width);

	void addImage(std::string id, Vector2f position, std::string path);

	void addImage(std::string id, Vector2f position, Vector2i size, BYTE* data);

	////////////////////////////////////////////////////////////////////////////

	Widget& widget(int i);

	int size();
};

}

