#pragma once
#include<iostream>
class Pixel
{
	int red;
	int green;
	int blue;
	int alpha;
	int selected = 0;
public:
	int getRed() { return red; }
	int getBlue() { return blue; }
	int getGreen() { return green; }
	int getAlpha() { return alpha; }
	bool getSelection() {
		return selected;
	}
	void minusSelection() { --selected; }
	void setRed(int r) { red = r; }
	void setBlue(int b) { blue = b; }
	void setGreen(int g) { green = g; }
	void setSelection() { selected++; }
	void setAlpha(int a) { alpha = a; }
	Pixel(int r, int g, int b, int a);
	friend std::ostream& operator<<(std::ostream& os, const Pixel& p) {
		return os << "(" << p.red << "," << p.green << "," << p.blue << "," << p.alpha <<")";
	}
	friend bool operator==(Pixel p1, Pixel p2) {
		if (p1 == p2) {
			return true;
		}
		else return false;
	};
	~Pixel();
};

