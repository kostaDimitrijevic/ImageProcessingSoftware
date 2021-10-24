#pragma once
#include"Rectangle.h"
#include<vector>
#include<string>
class Selection
{
private:
	std::vector<Rectangle> selection;
	std::string name_of_selection;
	bool active = false;
public:
	std::string getName() { return name_of_selection; };
	std::vector<Rectangle> getRectrangles() { return selection; };
	Selection(std::string name, bool );
	bool getActivity() { return active; }
	Selection() {};
	void AddRectangle(int x, int y, int h, int w);
	~Selection();
};

