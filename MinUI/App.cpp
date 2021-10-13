#include "App.h"

namespace MinUI
{

static void * routine(void * arg)
{
	App* app = (App*) arg;
	app->run();
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////

App::App() {}

App::~App() {}

////////////////////////////////////////////////////////////////////////////////

void App::setupX11Window(std::string title, float width, float height)
{
	//XInitThreads();

	m_size = {width, height};

	m_context.display_p = XOpenDisplay(NULL);

	if (m_context.display_p == NULL) {
		std::cerr << "Could not open the m_context.display_p !\n";
		throw std::exception();
	}

	int root_screen = XDefaultScreen(m_context.display_p);

	bool visual_found = XMatchVisualInfo(m_context.display_p, root_screen, 24, TrueColor, &m_context.info);

	if (!visual_found) {
		std::cerr << "No suitable visuals were found.\n";
		throw std::exception();
	}

	int depth      = m_context.info.depth;
	int screen     = m_context.info.screen;

	// TODO: center the window at start
	m_context.window = XCreateWindow(m_context.display_p, XRootWindow(m_context.display_p, screen),
	                                 0, 0, m_size.x * GRID_SIZE, m_size.y * GRID_SIZE, 0, depth, 0,
	                                 m_context.info.visual, 0, NULL);

	m_context.buffer = XCreatePixmap(m_context.display_p, XRootWindow(m_context.display_p, screen),
	                                 m_size.x * GRID_SIZE, m_size.y * GRID_SIZE, depth);

	m_context.gc = XDefaultGC(m_context.display_p, m_context.info.screen);

	////////////////////////////////////////////////////////////////////////////

	banDynamicResize();

	XStoreName(m_context.display_p, m_context.window, title.c_str());

	XMapWindow(m_context.display_p, m_context.window);

	XSetWindowBackground(m_context.display_p, m_context.window, codeFromColor(COLOR_BASE));
}

////////////////////////////////////////////////////////////////////////////////

void App::setupInputs()
{
	m_inputs = Inputs(m_context);
}

void App::setupFont()
{
	m_font= Font(DEFAULT_FONT_PATH, FONT_SIZE, m_context);
}

void App::setUpCanvas()
{
	m_root_canvas = Canvas("root", {0, 0}, {m_size.x, m_size.y}, "", Canvas::NOBORDER, 1);
}

////////////////////////////////////////////////////////////////////////////////

void App::banDynamicResize()
{
	XSizeHints* size_hints = XAllocSizeHints();

	size_hints->flags = PMinSize | PMaxSize;

	size_hints->min_width = m_size.x * GRID_SIZE;
	size_hints->max_width = m_size.x * GRID_SIZE;

	size_hints->min_height = m_size.y * GRID_SIZE;
	size_hints->max_height = m_size.y * GRID_SIZE;

	XSetWMNormalHints(m_context.display_p, m_context.window, size_hints);

	free(size_hints);
}

void App::setWindowSize(float width, float height)
{
	m_size = {width, height};

	XResizeWindow(m_context.display_p, m_context.window,
	              width * GRID_SIZE, height * GRID_SIZE);

	int depth      = m_context.info.depth;
	int screen     = m_context.info.screen;

	XFreePixmap(m_context.display_p, m_context.buffer);

	m_context.buffer = XCreatePixmap(m_context.display_p, XRootWindow(m_context.display_p, screen),
	                                 m_size.x * GRID_SIZE, m_size.y * GRID_SIZE, depth);

	m_root_canvas.resize(m_size.x, m_size.y);

	banDynamicResize();
}

void App::setWindowTitle(std::string title)
{
	XStoreName(m_context.display_p, m_context.window, title.c_str());
}

////////////////////////////////////////////////////////////////////////////////

Canvas& App::canvas(std::string id)
{
	Canvas * value = searchForCanvas(id, &m_root_canvas);

	if (value == nullptr)
		std::cerr << "Canvas '" << id << "' not found" << std::endl;

	return (*value);
}

Button& App::button(std::string id)
{
	Button * button = searchForWidget <Button> (id, &m_root_canvas);

	if (button == nullptr)
		std::cerr << "Button '" << id << "' not found" << std::endl;

	return (*button);
}

Entry& App::entry(std::string id)
{
	Entry * entry = searchForWidget <Entry> (id, &m_root_canvas);

	if (entry == nullptr)
		std::cerr << "Entry '" << id << "' not found" << std::endl;

	return (*entry);
}

Slider& App::slider(std::string id)
{
	Slider * slider = searchForWidget <Slider> (id, &m_root_canvas);

	if (slider == nullptr)
		std::cerr << "Slider '" << id << "' not found" << std::endl;

	return (*slider);
}

TrackBar& App::trackbar(std::string id)
{
	TrackBar * trackbar = searchForWidget <TrackBar> (id, &m_root_canvas);

	if (trackbar == nullptr)
		std::cerr << "TrackBar '" << id << "' not found" << std::endl;

	return (*trackbar);
}

Label& App::label(std::string id)
{
	Label * label = searchForWidget <Label> (id, &m_root_canvas);

	if (label == nullptr)
		std::cerr << "Label '" << id << "' not found" << std::endl;

	return (*label);
}

CheckBox& App::checkbox(std::string id)
{
	CheckBox * checkbox = searchForWidget <CheckBox> (id, &m_root_canvas);

	if (checkbox == nullptr)
		std::cerr << "CheckBox '" << id << "' not found" << std::endl;

	return (*checkbox);
}

Image& App::image(std::string id)
{
	Image * image = searchForWidget <Image> (id, &m_root_canvas);

	if (image == nullptr)
		std::cerr << "Image '" << id << "' not found" << std::endl;

	return (*image);
}

////////////////////////////////////////////////////////////////////////////////

void App::run()
{
	setupX11Window();
	setupInputs();
	setUpCanvas();
	setupFont();

	init();

	Timer timer;
	m_loop = true;

	////////////////////////////////////////////////////////////////////////

	while (m_loop) {
		timer.reset();

		m_inputs.update();

		if (m_inputs.state().close_request)
			m_loop = false;

		////////////////////////////////////////////////////////////////////

		m_root_canvas.update(m_inputs.state());

		m_root_canvas.render(m_context, m_font);

		////////////////////////////////////////////////////////////////////

		//XClearWindow(m_context.display_p, m_context.window);

		XCopyArea(m_context.display_p, m_context.buffer, m_context.window,
		          m_context.gc, 0, 0, m_size.x * GRID_SIZE, m_size.y * GRID_SIZE, 0, 0);

		///////////////////////////////////////////////////////////////////

		//XFlush(m_context.display_p);

		update();

		float elapsed  = timer.getTimeMS();
		//std::cout << "elapsed : "  << elapsed << std::endl;
		float pause = std::max(0.f, (1000 / FRAME_RATE) - elapsed);
		usleep((int) 1000 * pause);
	}

	//XFreeGC(m_context.display_p, m_context.gc);

	XDestroyWindow(m_context.display_p, m_context.window);
	XCloseDisplay(m_context.display_p);

}

void App::start()
{
	// TODO : check status
	int status = pthread_create(&m_thread, NULL, routine, this);

	if (status != 0) {
		std::cerr << "Failed to start the App thread" << std::endl;
		return;
	}
}

void App::join()
{
	pthread_join(m_thread, NULL);
}

void App::close()
{
	m_loop = false;
}

}
