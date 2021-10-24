#pragma once
#include "Layer.h"
#include <cmath>
#include<algorithm>
#include<vector>
class Operation
{
public:
	//virtual void Execute(Layer &lay, int c) = 0;
	virtual int getC() = 0;
	virtual void Execute() = 0;
	virtual void setLayer(Layer* l) = 0;
	virtual void setConstant(int c = 0) = 0;
	virtual void setBool(bool b) = 0;
	//virtual void Execute(vector<Operation*> comp) = 0;
};
