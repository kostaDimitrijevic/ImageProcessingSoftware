#pragma once
#include"BasicOperation.h"
class CompositOperation : public Operation{
private:
	Layer* lay;
	vector<Operation*> comp;
	std::string name;
	std::string path;
	void setBool(bool b) {};
	void setConstant(int c = 0) {};
	int getC() { return 1; }
public:
	void setLayer(Layer* l) { lay = l; };
	inline std::string getName() { return name; };
	inline std::string getPath() { return path; };
	inline void setPath(std::string p) { path = p; };
	vector<Operation*> getVector() { return comp; };
	CompositOperation(vector<Operation*> c, Layer* l, std::string n) :comp(c), lay(l),name(n) {};
	void Execute() {
		for (Operation* o : comp) {
			o->setLayer(lay);
			o->setBool(true);
			o->Execute();
		}
	}
};