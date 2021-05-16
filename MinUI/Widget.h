////////////////////////////////////////////////////////////////////////////////
// Widget.h
// -----------------------------------------------------------------------------
// Base class of all MinUI widgets.
// This class is abstract: each derived widgets must implement the methods 
// 'render()', 'update()', 'clone()' and 'id()'.
/////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Types.h"
#include "Draw.h"
#include "Inputs.h"
#include "Font.h"

#include <string>

namespace MinUI
{
class Widget
{
    protected :

	std::string m_id;

//	Vector2i m_position;
//	Vector2i m_dimension;

    public :

	virtual void render(X11Context& context, Font& font) = 0;

	virtual void update(InputState& input_state) = 0;

	virtual std::string id() = 0;

	virtual Widget* clone() = 0;

	virtual ~Widget() {}

	//void setPosition(int x, int y);
	//void setDimension(int w, int h);

};
}
