#pragma once
#include"Image.h"
class Formatter {
public:
	virtual Image import(std::string file, Image* i) = 0;
	virtual void expor(Image& picture, std::string file) = 0;
	friend class XMLFormatter;
};