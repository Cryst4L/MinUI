#include "Inputs.h"

namespace MinUI
{
Inputs::Inputs() {}

Inputs::Inputs(X11Context& context)
{
	init(context);
}

void Inputs::init(X11Context& context)
{
	m_input_state.close_request = false;

	m_context = context;

	long mask = ExposureMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask;

	XSelectInput(m_context.display_p, m_context.window, mask);

	m_delete_msg = XInternAtom(m_context.display_p, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(m_context.display_p, m_context.window, &m_delete_msg, 1);
}

void Inputs::update()
{
	m_input_state.close_request   = false;
	m_input_state.mouse.clicked   = false;
	m_input_state.keyboard.stroke = false;

	////////////////////////////////////////////////////////////////////////

	Window root, child;
	int root_x, root_y;
	int mouse_x, mouse_y;

	unsigned int event_mask;

	XQueryPointer(m_context.display_p, m_context.window, &root, &child,
	              &root_x, &root_y, &mouse_x, &mouse_y, &event_mask);

	m_input_state.mouse.x = mouse_x;
	m_input_state.mouse.y = mouse_y;

	m_input_state.mouse.pressed = (event_mask & Button1Mask);

	////////////////////////////////////////////////////////////////////////

	XEvent event;

	while (XPending(m_context.display_p) > 0) {
		XNextEvent(m_context.display_p, &event);

		if (event.type == Expose)
			std::cout << "expose" << std::endl;

		if (event.type == ButtonRelease) {

			if (event.xbutton.button == 1)
				m_input_state.mouse.clicked = true;
		}

		if (event.type == KeyPress) {

			m_input_state.keyboard.stroke = true;

			m_input_state.keyboard.code = event.xkey.keycode;

			//TODO: Add numpad support

			KeySym symbol = XLookupKeysym(&event.xkey, 0);

			if ((symbol != XK_Shift_L) && (symbol != XK_Shift_R)) {

				int caps = !((event.xkey.state & ShiftMask) == 0);
				symbol = XLookupKeysym(&event.xkey, caps);
				
				m_input_state.keyboard.symbol = symbol;
				std::cout << std::hex << "KeySym : 0x" << symbol << std::endl;
			}

		}

		if (event.type == ClientMessage) {
			if (event.xclient.data.l[0] == (int) m_delete_msg) {
				m_input_state.close_request = true;
			}
		}

	}

}

InputState& Inputs::state()
{
	return m_input_state;
}

}
