#pragma once
#include<vector>
#include <algorithm>
#include "CompositOperation.h"
#include"Selection.h"
#include"Operation.h"
#include"Layer.h"
#include<cstdint>
#include<map>
#include<functional>
using namespace std;
class Image
{
private:
	double ap = 1;
	vector<Layer> image;
	double a = 0;
	uint8_t b = 0;
	uint8_t r = 0;
	uint8_t g = 0;
	map<std::string, Selection> selection_map;
	map<std::string , Operation*> operation_map;
	vector<CompositOperation*>  composit_vector;
public:
	Image();
	void addLayer(Layer& newLayer);

	void deleteLayer(Layer l);

	void removeLayer(function<bool(Layer l) > predicate);

	void addOperationToMap(std::string operation, Operation* o);

	vector<Layer>& getImage() { return image; } ;

	void operationA(Pixel p, double LayerTransparecy);

	void calculateAp(double an, double LayerTransparency);

	void operationRGB( Pixel p, double LayerTransparecy);

	void resetRGBA();

	void addSelectionToMap(std::string name, Selection s);

	Selection getSelectionFromMap(std::string name);

	map<std::string, Selection>& get_Selection_Map() {return selection_map;};

	void doOperation(Operation* o, int c);

	void setOperation_map(map<std::string, Operation*> m) { operation_map = m; }

	void select(std::string);

	void deactivateSelection(std::string);

	double getA()const { return a; }

	uint8_t getB()const { return b; }

	uint8_t getR()const { return r; }

	uint8_t getG()const { return g; }

	Operation* takeOperation(std::string operation);

	void colorSelection(std::string name_of_selection, int r, int g, int b);

	void doCompositOperation(Operation* o);

	void addToCompositVector(CompositOperation* c);

	CompositOperation* takeFromCompositVector(std::string name);

	vector<CompositOperation*> getComposit_vector() { return composit_vector; }

	~Image();
};

