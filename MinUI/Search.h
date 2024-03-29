////////////////////////////////////////////////////////////////////////////////
// Search.h
// -----------------------------------------------------------------------------
// Implements the searching algorithms.
// The canvas set is structured as a tree in which each canvas act as a node.
// To retreive a canvas, one must perform a search over the canvas tree.
// Similarly widgets are retreived by going over this tree and checking the 
// canvas containers content.
// The search algorithms are both recursive. The widget search is implemented 
// using a template to ensure proper polymorphism.  
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Button.h"
#include "Canvas.h"

namespace MinUI
{
inline Canvas* searchForCanvas(std::string id, Canvas* root)
{
	//found = false;
	Canvas * value = nullptr;

	if (root->id() == id) {
		value = root;
		//found = true;
	} else {
		for (int i = 0; i < (int) root->childs().size(); i++) {
			value = searchForCanvas(id, &(root->childs()[i]));

			if (value != nullptr) {
				//found = true;
				break;
			}
		}
	}

	return value;
}

template <class T>
inline T* searchForWidget(std::string id, Canvas* root)
{
	T * value = nullptr;
	bool found = false;

	for (int i = 0; i < root->container().size(); i++) {

		Widget* widget = &(root->container().widget(i));

		bool same_id = (widget->id() == id);
		bool same_type = ((dynamic_cast <T*> (widget)) != nullptr);

		if (same_type && same_id) {
			value = (dynamic_cast <T*> (widget));
			found = true;
			break;
		}
	}

	if (!found) {
		for (int i = 0; i < (int) root->childs().size(); i++) {
			value = searchForWidget <T> (id, (&root->childs()[i]));

			if (value != nullptr)
				break;
		}
	}

	return value;
}


}

