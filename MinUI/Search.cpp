#include "Search.h"

/*
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
*/

////////////////////////////////////////////////////////////////////////////////

/*bool searchForCanvas(std::string id, Canvas& root, Canvas& rvalue)
{
	//std::cout << root.id() << std::endl;
	bool found = false;

	if (root.id() == id) {
		//std::cout << "found" << std::endl;
		rvalue = root;
		found = true;
	} else {
		for (int i = 0; i < root.childs().size(); i++) {
			found |= searchForCanvas(id, root.childs()[i], rvalue);
		}
	}

	return found;
}
*/

/*
template <class T>
bool searchForWidget(std::string id, Canvas& root, T& rvalue)
{
	bool found = false;

	for (int i = 0; i < root.container().size(); i++) {

		Widget* widget = &(root.container().widget(i));
		bool same_id = (root.container().widget(i).id() == id);
		bool same_type = ((dynamic_cast <T*> (widget)) != nullptr);

		if (same_type && same_id) {
			rvalue = *(dynamic_cast <T*> (widget));
			found = true;
			break;
		}
	}

	if (!found) {
		for (int i = 0; i < root.childs().size(); i++) {
			found |= searchForWidget<T>(id, root.childs()[i], rvalue);
			if (found)
				break;
		}
	}

	return found;
}
*/


