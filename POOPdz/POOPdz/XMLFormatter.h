#pragma once
#include "Formatter.h"
#include "BMPFormatter.h"
#include "PAMFormatter.h"
#include"tinyxml2.h"
using namespace tinyxml2;

class XMLh :public Formatter {
private:
public:
	Image import(std::string file, Image *i);
	Operation* importComposit(std::string file, Image *i);
	void exportComposit(Image i, CompositOperation*);
	void expor(Image& i, std::string file);
};