////////////////////////////////////////////////////////////////////////////////
// App.h
// -----------------------------------------------------------------------------
// Base class for all MinUI applications.
// This class is abstract - derived applications must fill the methods 'init' 
// and 'update'. The resulting App can run in the main (with the method 'run') 
// or in its own thread (with the methods 'start' and 'join').
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Widget.h"
#include "Inputs.h"
#include "Types.h"
#include "Font.h"
#include "Draw.h"
#include "Utils.h"
#include "Canvas.h"
#include "Timer.h"
#include "Search.h"

#include "Label.h"
#include "Button.h"
#include "Slider.h"
#include "Entry.h"
#include "Image.h"

#include <vector>
#include <cmath>
#include <exception>
#include <iostream>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>

#include <pthread.h>

namespace MinUI
{

class App
{
    private :

	Vector2f   m_size;
	X11Context m_context;
	pthread_t  m_thread;
	Inputs     m_inputs;
	Font       m_font;
	Canvas      m_root_canvas;
	bool       m_loop;

	void setupX11Window(std::string title = "MinUI",
	                    float width = 8, float height = 8);

	void setupInputs();
	void setupFont();
	void setUpCanvas();
	void banDynamicResize();

    public :

	virtual void init() = 0;
	virtual void update() = 0;

	////////////////////////////////////////////////////////////////////////////

	App();
	~App();

	////////////////////////////////////////////////////////////////////////////

	void setWindowSize(float width, float height);

	void setWindowTitle(std::string title);

	////////////////////////////////////////////////////////////////////////////

	Canvas& canvas(std::string id);

	Button& button(std::string id);

	Entry& entry(std::string id);

	Slider& slider(std::string id);

	TrackBar& trackbar(std::string id);

	Label& label(std::string id);

	CheckBox& checkbox(std::string id);

	Image& image(std::string id);

	////////////////////////////////////////////////////////////////////////////

	void run();

	void start();

	void join();

	void close();
};


}
