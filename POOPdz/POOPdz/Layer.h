#pragma once
#include<iostream>
#include<vector>
#include<iterator>
#include<functional>
#include"Pixel.h"
#include"Rectangle.h"
#include<algorithm>
using namespace std;
class Layer
{
private:
	int transparency;
	bool active = true;
	vector<vector<Pixel>> layer;
	int selected = 0;
	bool visible = true;
	std::string name;
public:
	vector<vector<Pixel>>& getLayer() { return layer; }

	Layer(int m, int n);
	void export_set_Selection(int s) { selected = s; }

	void setSelection() { selected ++; }

	int getSelection() { return selected; }

	void minusSelection() { --selected; }

	void setTransparency(int t) { transparency = t; }

	int getTransparency() const { return transparency; }

	void setActivity(bool a) { active = a; }

	bool getActivity() { return active;}

	void setVisibility(bool v) { visible = v; }

	bool getVisibility() { return visible; }

	void extendLayerY(Layer &l, Layer sizeLay);

	void extendLayerX(Layer &l, Layer sizeLay);

	void doRectangle(Rectangle);

	void setName(std::string n) { name = n; }

	std::string getName() { return name; }

	int median(vector<int> canal);

	void deselectRectangle(Rectangle);


	Layer() {};

	friend ostream& operator<<(ostream& os, const Layer l) {
		for (vector<Pixel> row : l.layer) {
			for (Pixel pixel : row) {
				cout << pixel;
			}
			cout << endl;
		}
		return os;
	}

	~Layer();
};



