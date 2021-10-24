#include "Pixel.h"
Pixel::Pixel(int r, int g, int b, int a) {
	red = std::abs(r) % 256;
	green = std::abs(g) % 256;
	blue = std::abs(b) % 256;
	alpha = std::abs(a) % 256;
}
Pixel::~Pixel()
{
}
