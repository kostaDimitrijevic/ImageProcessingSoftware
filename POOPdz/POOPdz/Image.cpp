#include "Image.h"
#include "BasicOperation.h"
void Image::addLayer(Layer& newLayer) {
	if (image.empty()) {
		image.push_back(newLayer);
	}
	else {

		if (newLayer.getLayer().size() < image.front().getLayer().size() && newLayer.getLayer()[0].size() > image.front().getLayer()[0].size()) {
			for (Layer& l : image) {
				l.extendLayerX(l, newLayer);
			}
			newLayer.extendLayerY(newLayer, image.front());
		}
		if (newLayer.getLayer().size() > image.front().getLayer().size() && newLayer.getLayer()[0].size() < image.front().getLayer()[0].size()) {
			newLayer.extendLayerX(newLayer, image.front());
			for (Layer& l : image) {
				l.extendLayerY(l, newLayer);
			}
		}
		if (newLayer.getLayer().size() < image.front().getLayer().size() && newLayer.getLayer()[0].size() < image.front().getLayer()[0].size()) {
			newLayer.extendLayerX(newLayer, image.front());
			newLayer.extendLayerY(newLayer, image.front());
		}
		if (newLayer.getLayer().size() > image.front().getLayer().size() && newLayer.getLayer()[0].size() > image.front().getLayer()[0].size()) {
			for (Layer& l : image) {
				l.extendLayerY(l, newLayer);
				l.extendLayerX(l, newLayer);
			}
		}
		image.push_back(newLayer);
	}
}
Image::Image(){}

void Image::deleteLayer(Layer l) {
	for (Layer& lay : image) {
		if (lay.getName() == lay.getName()) {
			removeLayer([&lay](Layer l) {if( lay.getName() == l.getName()) return true; });
		}
	}
}
Selection Image::getSelectionFromMap(std::string s) { return selection_map[s]; }

void Image::removeLayer(function<bool(Layer l) > predicate) {
	auto iter = remove_if(image.begin(), image.end(), predicate);
	image.erase(iter, image.end());
}

void Image::calculateAp(double an, double LayerTransparency) {
	ap = ap - (ap * an * LayerTransparency / 100) /255;
}
void Image::operationA(Pixel p, double LayerTransparency) {
	a = a + (((double)p.getAlpha() / 255) * ap * LayerTransparency / 100);
}
void Image::operationRGB(Pixel p, double LayerTransparency) {
	b = b + (p.getBlue() * ap * ((double)p.getAlpha() / 255 )* LayerTransparency / 100);
	r = r + (p.getRed() * ap * ((double)p.getAlpha() / 255)* LayerTransparency / 100);
	g = g + (p.getGreen() * ap * ((double)p.getAlpha() / 255)* LayerTransparency / 100);
	calculateAp(p.getAlpha(), LayerTransparency);
}
void Image::resetRGBA(){
	ap = 1;
	a = 0;
	b = 0;
	r = 0;
	g = 0;
}
void Image::addOperationToMap(std::string operation, Operation* o) {
	operation_map[operation] = o;
}
Operation* Image::takeOperation(std::string operation) {
	Layer l(1, 1);
	if (operation == "Add") {
		operation_map["Add"] = new Add(&l, 0);
	}
	if (operation == "Subtraction") {
		operation_map["Subtraction"] = new Subtraction(&l, 0);
	}
	if (operation == "InvertedSubtraction") {
		operation_map["InvertedSubtraction"] = new InvSubtraction(&l, 0);
	}
	if (operation == "Multiplication") {
		operation_map["Multiplication"] = new Multiplication(&l, 0);
	}
	if (operation == "Divide") {
		operation_map["Divide"] = new Divide(&l, 0);
	}
	if (operation == "InvertedDivision") {
		operation_map["InvertedDivison"] = new InvDivide(&l, 0);
	}
	if (operation == "Power") {
		operation_map["Power"] = new Power(&l, 0);
	}
	if (operation == "Log") {
		operation_map["Log"] = new Log(&l, 0);
	}
	if (operation == "Minimum") {
		operation_map["Minimum"] = new Min(&l, 0);
	}
	if (operation == "Maximum") {
		operation_map["Maximum"] = new Max(&l, 0);
	}
	if (operation == "Inversion") {
		operation_map["Inversion"] = new Inversion(&l);
	}
	if (operation == "Grey") {
		operation_map["Grey"] = new Grey(&l);
	}
	if (operation == "BlackAndWhite") {
		operation_map["BlackAndWhite"] = new Black_and_white(&l);
	}
	if (operation == "Median") {
		operation_map["Median"] = new Median(&l);
	}
	return operation_map[operation];
}

void Image::addToCompositVector(CompositOperation * c) {
	composit_vector.push_back(c);
}

CompositOperation* Image::takeFromCompositVector(std::string name) {
	for (CompositOperation* i : composit_vector) {
		if (i->getName() == name) {
			return i;
		}
	}
	return nullptr; 
}

void Image::addSelectionToMap(std::string name, Selection s) {
	selection_map[name] = s;
}
void Image::select(std::string name) {
	Selection s = selection_map[name];
	for (Rectangle& r : s.getRectrangles()) {
		for (Layer& l : image) {
			if(s.getActivity())
				l.doRectangle(r);
		}
	}
}
void Image::deactivateSelection(std::string name) {
	Selection s = selection_map[name];
	for (Rectangle& r : s.getRectrangles()) {
		for (Layer& l : image) {
			l.deselectRectangle(r);
		}
	}
	selection_map.erase(name);
}

void Image::colorSelection(std::string name_of_selection, int r, int g, int b) {
	Selection s = selection_map[name_of_selection];
	for (Rectangle &rec : s.getRectrangles()) {
		for (Layer& l : image) {
			for (int i = rec.getY(); i < rec.getHeight(); i++) {
				for (int j = rec.getX(); j < rec.getWidth(); j++) {
					l.getLayer()[i][j].setRed(r);
					l.getLayer()[i][j].setGreen(g);
					l.getLayer()[i][j].setBlue(b);
				}
			}
		}
	}
}

void Image::doOperation(Operation *o, int c) {
	for (Layer& lay : image) {
		o->setLayer(&lay);
		o->setConstant(c);
		o->setBool(false);
		o->Execute();
	}
}

void Image::doCompositOperation(Operation* o) {
	for (Layer& l : image) {
		o->setLayer(&l);
		o->Execute();
	}
	for (Layer& l : image) {
		for (vector<Pixel>& row : l.getLayer()) {
			for (Pixel &p : row) {
				p.setRed(p.getRed() % 256);
				p.setBlue(p.getBlue() % 256);
				p.setGreen(p.getGreen() % 256);
				p.setAlpha(p.getAlpha() % 256);
			}
		}
	}
}
Image::~Image()
{
}
