#pragma once
class Rectangle
{
private:
	int x;
	int y;
	int height;
	int width;
public:
	Rectangle(int x, int y, int height, int width);
	int getX() { return x; };
	int getY() { return y; };
	int getHeight() { return height; };
	int getWidth() { return width; };
	~Rectangle();
};

