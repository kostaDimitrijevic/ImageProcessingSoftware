#include "Selection.h"



Selection::Selection(std::string name, bool a) : name_of_selection(name), active(a){}

void Selection::AddRectangle(int x, int y, int h, int w) {
	Rectangle r(x, y, h, w);
	selection.push_back(r);
}


Selection::~Selection()
{
}
