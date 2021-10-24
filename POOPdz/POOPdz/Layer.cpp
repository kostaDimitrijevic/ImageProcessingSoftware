#include "Layer.h"
Layer::Layer(int m, int n)
{	
	Pixel p(0, 0, 0, 0);
	for (int i = 0; i < m; i++) {
		vector<Pixel> temp;
		for (int j = 0; j < n; j++) {
			temp.push_back(p);
		}
		layer.push_back(temp);
	}
}
void Layer::extendLayerY(Layer &l, Layer sizeLay) {
	Pixel p(0, 0, 0, 0);
	int m1 = l.getLayer().size(); // br elemenata novog lejera po y osi
	int m2 = sizeLay.getLayer().size(); // br elemenata lejera slike po y osi
	for (int i = m1; i < m2; i++) {
		vector<Pixel> temp;
		for (int j = 0; j < sizeLay.getLayer()[0].size(); j++) {
			temp.push_back(p);
		}
		l.getLayer().push_back(temp);
	}
}
void Layer::extendLayerX(Layer& l, Layer sizeLay){
		Pixel p(0, 0, 0, 0);
		for (int i = 0; i < l.getLayer().size(); i++) {
			for (int j = l.getLayer()[i].size(); j < sizeLay.getLayer()[0].size(); j++) {
				l.getLayer()[i].push_back(p);
			}
		}
}
void Layer::doRectangle(Rectangle r) {
	if (r.getY() + r.getHeight() <= this->getLayer().size() && r.getX() + r.getWidth() <= this->getLayer().size()){
		this->setSelection();
		for (int i = r.getY(); i < r.getY() + r.getHeight(); i++) {
			for (int j = r.getX(); j < r.getX() + r.getWidth(); j++) {
				this->getLayer()[i][j].setSelection();
			}
		}
	}
}
void Layer::deselectRectangle(Rectangle r) {
	if (r.getY() + r.getHeight() <= this->getLayer().size() && r.getX() + r.getWidth() <= this->getLayer().size()) {
		this->minusSelection();
		for (int i = r.getY(); i < r.getY() + r.getHeight(); i++) {
			for (int j = r.getX(); j < r.getX() + r.getWidth(); j++) {
				if (this->getLayer()[i][j].getSelection() >= 1) this->getLayer()[i][j].minusSelection();
			}
		}
	}
}
int Layer::median(vector<int> canal) {
	size_t size = canal.size();
	sort(canal.begin(), canal.end());
	if (size % 2 == 0)
	{
		return (canal[size / 2 - 1] + canal[size / 2]) / 2;
	}
	else
	{
		return canal[size / 2];
	}
}


Layer::~Layer()
{
}
