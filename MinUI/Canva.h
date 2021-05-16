////////////////////////////////////////////////////////////////////////////////
// Canva.h
// -----------------------------------------------------------------------------
// Canvas serve both as a structuring element of the GUI (by providing box 
// shapes where the Widgets are placed), and as a storage for the Widgets 
// themselves. 
// The set of all canvas is structured as a Tree, starting from the canva 'root' 
// contained in the App.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Types.h"
#include "Widget.h"
#include "Utils.h"
#include "Draw.h"

#include "Container.h"

#include "Label.h"
#include "Button.h"
#include "Slider.h"
#include "Entry.h"
#include "CheckBox.h"

#include <cmath>

namespace MinUI
{

class Canva
{
    public:

	enum BorderEnum {OUTLINE = 0, MARGIN = 1, NOBORDER = 2};

    private :

	std::string m_id;

	Vector2f m_position;
	Vector2f m_dimension;

	Container m_container;

	std::vector <Canva> m_childs;

	Vector2f m_widget_padding;
	Vector2f m_canva_padding;

	std::string m_title;
	BorderEnum m_style;
	bool m_parity;

	//TODO: add a check boundaries
	// bool checkBoundaries(Vector2f position, Vector2f dimension)

	void renderSelf(X11Context& context, Font& font);

    public :

	Canva();

	Canva(std::string id, Vector2f position, Vector2f dimension,
	      std::string title = "", BorderEnum style = MARGIN, bool parity = 0);

	~Canva();

	////////////////////////////////////////////////////////////////////////////

	std::string id();

	Canva& canva(int index);

	std::vector <Canva> & childs();

	void resize(float width, float height);

	Container& container();

	////////////////////////////////////////////////////////////////////////////

	void render(X11Context& context, Font& font);

	void update(InputState& input_state);

	////////////////////////////////////////////////////////////////////////////

	void addCanva(std::string id, Vector2f position, Vector2f dimension,
	              std::string title, BorderEnum style = MARGIN);

	void addLabel(std::string id, std::string label, Vector2f position);

	void addButton(std::string id, std::string text, Vector2f position, Vector2f dimension);

	void addSlider(std::string id, Vector2f position, float width, Vector2f range = {0, 1});

	void addEntry(std::string id, Vector2f position, float width, bool numeric = false);

	void addCheckBox(std::string id, std::string text, Vector2f position);

	void addTrackBar(std::string id, Vector2f position, float width);

	void addImage(std::string id, Vector2f position, std::string path);

	void addImage(std::string id, Vector2f position, Vector2i size, BYTE* data);
};

}

