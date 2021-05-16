////////////////////////////////////////////////////////////////////////////////
// Inputs.h
// -----------------------------------------------------------------------------
// The 'Inputs' class processes the X11 events and fill the 'InputState' 
// structure  which is used to update all the widgets.
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Types.h"
#include <iostream>

namespace MinUI
{

typedef struct {
	int x, y;
	bool pressed;
	bool clicked;
} MouseState;

typedef struct {
	int code;
	int symbol;
//	char* label;
	bool stroke;
//	bool caps;
} KeyboardState;


typedef struct {
	MouseState mouse;
	KeyboardState keyboard;
	bool close_request;
} InputState;


class Inputs
{
    private :

	InputState m_input_state;
	X11Context m_context;
	Atom m_delete_msg;

	void init(X11Context& context);

    public :

	Inputs();

	Inputs(X11Context& context);

	void update();

	InputState& state();

};

}
