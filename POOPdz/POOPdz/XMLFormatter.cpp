#include"XMLFormatter.h"
#include <regex>

Operation* XMLh::importComposit(std::string file, Image *i) {
	ifstream pic;
	pic.open(file, ios::in);
	std::string file_as_string;
	std::regex oper("<([0-9A-za-z. ]+) Konstanta=\"([0-9A-Za-z]+)\"/>");
	std::smatch n;
	int c;
	vector<Operation*> temp;
	Operation* o;
	while (!regex_search(file_as_string, n, oper) && file_as_string != "</Composit>") {
		std::getline(pic, file_as_string);
	}
	while (regex_search(file_as_string, n, oper)) {
		bool flag = false;
		std::string name = n.str(1);
		if (n.str(2) != "nema")
			c = stoi(n.str(2));
		if (name == "Add") {
			o = i->takeOperation(name);
			o->setConstant(c);
			flag = true;
		}
		if (name == "Subtraction") {
			o = i->takeOperation(name);
			o->setConstant(c);
			flag = true;
		}
		if (name == "InvertedSubtraction") {
			o = i->takeOperation(name);
			o->setConstant(c);
			flag = true;
		}
		if (name == "Multiplication") {
			o = i->takeOperation(name);
			o->setConstant(c);
			flag = true;
		}
		if (name == "Divide") {
			o = i->takeOperation(name);
			o->setConstant(c);
			flag = true;
		}
		if (name == "InvertedDivision") {
			o = i->takeOperation(name);
			o->setConstant(c);
			flag = true;
		}
		if (name == "Power") {
			o = i->takeOperation(name);
			o->setConstant(c);
			flag = true;
		}
		if (name == "Log") {
			o = i->takeOperation(name);
			o->setConstant(c);
			flag = true;
		}
		if (name == "Absolute") {
			o = i->takeOperation(name);
			flag = true;
		}
		if (name == "Minimum") {
			o = i->takeOperation(name);
			o->setConstant(c);
			flag = true;
		}
		if (name == "Maximum") {
			o = i->takeOperation(name);
			o->setConstant(c);
			flag = true;
		}
		if (name == "Inversion") {
			o = i->takeOperation(name);
			flag = true;
		}
		if (name == "Grey") {
			o = i->takeOperation(name);
			flag = true;
		}
		if (name == "BlackAndWhite") {
			o = i->takeOperation(name);
			flag = true;
		}
		if (name == "Median") {
			o = i->takeOperation(name);
			flag = true;
		}
		if(!flag) {
			o = importComposit(name, i);
			temp.push_back(o);
			std::getline(pic, file_as_string);
			continue;
		}
		temp.push_back(o);
		std::getline(pic, file_as_string);
	}
	Layer help(1, 1);
	Operation* composit = new CompositOperation(temp, &help, file);
	i->addToCompositVector((CompositOperation*)composit);
	return composit;
}

Image XMLh::import(std::string file, Image *i) {
	Formatter* f1 = new BMPh;
	Formatter* f2 = new PAMh;
	ifstream pic;
	pic.open(file);
	std::string file_as_string;
	std::regex r("<Width width=\"([0-9]+)\"/>");
	std::smatch w;
	std::getline(pic, file_as_string);
	while (!regex_search(file_as_string, w, r)) { 
		std::getline(pic, file_as_string);
	}
	std::string wid = w.str(1);
	int width = stoi(wid);
	std::regex r1("<Height height=\"([0-9]+)\"/>");
	std::smatch h;
	while (!regex_search(file_as_string, h, r1)) {
		std::getline(pic, file_as_string);
	}
	std::string hh = h.str(1);
	int height = stoi(hh);
	std::regex lay("<Layer active=\"([a-z]+)\" name=\"([0-9A-Za-z\.]+)\" selected=\"([0-9]+)\" transparency=\"([0-9]+)\" visible=\"([a-z]+)\"/>");
	std::smatch l;
	while (!regex_search(file_as_string, h, lay)) {
		std::getline(pic, file_as_string);
	}
	while (regex_search(file_as_string, l, lay)) {
		bool visible = false, active = false;
		if (l.str(1) == "true")active = true;
		if (l.str(5) == "true")visible = true;
		int selected = stoi(l.str(3));
		int transparency = stoi(l.str(4));
		std::regex n("[0-9A-Za-z]+(.bmp)");
		std::smatch ex;
		std::string name = l.str(2);
		regex_search(name, ex, n);
		if (".bmp" == ex.str(1)) {
			*i = f1->import(name, i);
		}
		else
			*i = f2->import(name, i);
		for (Layer &l : i->getImage()) {
			if (l.getName() == name) {
				l.setActivity(active);
				l.setTransparency(transparency);
				l.setVisibility(visible);
				l.export_set_Selection(selected);
			}
		}
		std::getline(pic, file_as_string);
	}
	std::regex s("<Selection active=\"([A-Za-z]+)\" name=\"([0-9A-Za-z]+)\">");
	std::regex rec("<Rectangle height=\"([0-9]+)\" width=\"([0-9]+)\" x=\"([0-9]+)\" y=\"([0-9]+)\"/>");
	std::regex check("(</Selection>)");
	std::smatch ss;
	std::smatch	rr;
	std::smatch ch;
	while (!regex_search(file_as_string, ss, s) && file_as_string!="</Image>") {
		std::getline(pic, file_as_string);
	}
	while (regex_search(file_as_string, ss, s)) {
		std::string name = ss.str(2);
		bool active = false;
		if (ss.str(1) == "true")active = true;
		Selection select(name, active);
		std::getline(pic, file_as_string);
		while (regex_search(file_as_string, rr, rec)) {
			select.AddRectangle(stoi(rr.str(3)), stoi(rr.str(4)), stoi(rr.str(1)), stoi(rr.str(2)));
			i->addSelectionToMap(select.getName(), select);
			i->select(select.getName());
			std::getline(pic, file_as_string);
		}
		std::getline(pic, file_as_string);
	}
	std::regex comp("<Composit name=\"([0-9A-Za-z\.]+)\"/>");
	std::smatch mcomp;
	while (!regex_search(file_as_string, mcomp, comp) && file_as_string!="</Image>") {
		std::getline(pic, file_as_string);
	}
	while (regex_search(file_as_string, mcomp, comp)) {
		std::string name = mcomp.str(1);
		//std::string path = mcomp.str(2);
		importComposit(name, i);
		std::getline(pic, file_as_string);
	}
	return *i;
}
void XMLh::expor(Image& i, std::string file) {
	XMLDocument* xmlDoc = new XMLDocument();
	XMLNode * pRoot = xmlDoc->NewElement("Image");
	xmlDoc->InsertFirstChild(pRoot);
	XMLElement* pDimensions = xmlDoc->NewElement("Dimensions");
	XMLElement* pElement = xmlDoc->NewElement("Layers");
	Formatter *f = new BMPh();
	XMLElement* width = xmlDoc->NewElement("Width");
	int w = i.getImage().front().getLayer()[0].size();
	width->SetAttribute("width", w);
	pDimensions->InsertEndChild(width);
	XMLElement* height = xmlDoc->NewElement("Height");
	int h = i.getImage().front().getLayer().size();
	height->SetAttribute("height", h);
	pDimensions->InsertEndChild(height);
	pRoot->InsertEndChild(pDimensions);
	Image* temp = new Image();
	for (Layer l : i.getImage()) {	
		temp->addLayer(l);
		f->expor(*temp, l.getName());
		temp->deleteLayer(l);
		XMLElement* ElemLayer = xmlDoc->NewElement("Layer");
		ElemLayer->SetAttribute("active", l.getActivity());
		ElemLayer->SetAttribute("name", l.getName().c_str());
		ElemLayer->SetAttribute("selected", l.getSelection());
		ElemLayer->SetAttribute("transparency", l.getTransparency());
		ElemLayer->SetAttribute("visible", l.getVisibility());
		pElement->InsertEndChild(ElemLayer);		
	}
	pRoot->InsertEndChild(pElement);
	XMLElement* selections = xmlDoc->NewElement("Selections");
	for (pair<const std::string, Selection> s : i.get_Selection_Map()) {
		XMLElement* Selection = xmlDoc->NewElement("Selection");
		Selection->SetAttribute("active", s.second.getActivity());
		Selection->SetAttribute("name", s.first.c_str());
		for (Rectangle r : s.second.getRectrangles()) {
			XMLElement* SelectionRectangle = xmlDoc->NewElement("Rectangle");
			SelectionRectangle->SetAttribute("height", r.getHeight());
			SelectionRectangle->SetAttribute("width", r.getWidth());
			SelectionRectangle->SetAttribute("x", r.getX());
			SelectionRectangle->SetAttribute("y", r.getY());
			Selection->InsertEndChild(SelectionRectangle);
		}
		selections->InsertEndChild(Selection);
	}
	pRoot->InsertEndChild(selections);
	//XMLElement* Compelement = xmlDoc->NewElement("CompositFunctions");
	for (CompositOperation* j : i.getComposit_vector()) {
		exportComposit(i, j);
		//XMLElement* composit = xmlDoc->NewElement("Composit");
		//composit->SetAttribute("name", (j->getName()).c_str());
		//composit->SetAttribute("path", j->getPath().c_str());
		//Compelement->InsertEndChild(composit);
	}
	//pRoot->InsertEndChild(Compelement);
	xmlDoc->SaveFile(file.c_str());
}

void XMLh::exportComposit(Image i, CompositOperation* comp) {
	XMLDocument* xmlOperation = new XMLDocument();
	XMLNode* root = xmlOperation->NewElement("Composit");
	xmlOperation->InsertFirstChild(root);
	std::string path;
	std::string name = comp->getName().c_str();
	XMLElement* composit = xmlOperation->NewElement((comp->getName()).c_str());
	root->InsertEndChild(composit);
	path = "Composit/" + comp->getName();
	comp->setPath(path);
	//path = comp->getName() + ".fun";
	for (Operation* o : comp->getVector()) {
		if (typeid(*o) == typeid(Add)) {
			XMLElement* operation = xmlOperation->NewElement("Add");
			int c = o->getC();
			operation->SetAttribute("Konstanta", c);
			composit->InsertEndChild(operation);
		}
		if (typeid(*o) == typeid(Subtraction)) {
			XMLElement* operation = xmlOperation->NewElement("Subtraction");
			int c = o->getC();
			operation->SetAttribute("Konstanta", c);
			composit->InsertEndChild(operation);
		}
		if (typeid(*o) == typeid(InvSubtraction)) {
			XMLElement* operation = xmlOperation->NewElement("InvertedSubtraction");
			int c = o->getC();
			operation->SetAttribute("Konstanta", c);
			composit->InsertEndChild(operation);
		}
		if (typeid(*o) == typeid(Multiplication)) {
			XMLElement* operation = xmlOperation->NewElement("Multiplication");
			int c = o->getC();
			operation->SetAttribute("Konstanta", c);
			composit->InsertEndChild(operation);
		}
		if (typeid(*o) == typeid(Divide)) {
			XMLElement* operation = xmlOperation->NewElement("Divide");
			int c = o->getC();
			operation->SetAttribute("Konstanta", c);
			composit->InsertEndChild(operation);
		}
		if (typeid(*o) == typeid(InvDivide)) {
			XMLElement* operation = xmlOperation->NewElement("InvertedDivision");
			int c = o->getC();
			operation->SetAttribute("Konstanta", c);
			composit->InsertEndChild(operation);
		}
		if (typeid(*o) == typeid(Power)) {
			XMLElement* operation = xmlOperation->NewElement("Power");
			int c = o->getC();
			operation->SetAttribute("Konstanta", c);
			composit->InsertEndChild(operation);
		}
		if (typeid(*o) == typeid(Log)) {
			XMLElement* operation = xmlOperation->NewElement("Log");
			int c = o->getC();
			operation->SetAttribute("Konstanta", c);
			composit->InsertEndChild(operation);
		}
		if (typeid(*o) == typeid(Abs)) {
			XMLElement* operation = xmlOperation->NewElement("Absolute");
			operation->SetAttribute("Konstanta", "nema");
			composit->InsertEndChild(operation);
		}
		if (typeid(*o) == typeid(Min)) {
			XMLElement* operation = xmlOperation->NewElement("Minimum");
			int c = o->getC();
			operation->SetAttribute("Konstanta", c);
			composit->InsertEndChild(operation);
		}
		if (typeid(*o) == typeid(Max)) {
			XMLElement* operation = xmlOperation->NewElement("Maximum");
			int c = o->getC();
			operation->SetAttribute("Konstanta", c);
			composit->InsertEndChild(operation);
		}
		if (typeid(*o) == typeid(Inversion)) {
			XMLElement* operation = xmlOperation->NewElement("Inversion");
			operation->SetAttribute("Konstanta", "nema");
			composit->InsertEndChild(operation);
		}
		if (typeid(*o) == typeid(Grey)) {
			XMLElement* operation = xmlOperation->NewElement("Grey");
			operation->SetAttribute("Konstanta", "nema");
			composit->InsertEndChild(operation);
		}
		if (typeid(*o) == typeid(Black_and_white)) {
			XMLElement* operation = xmlOperation->NewElement("BlackAndWhite");
			operation->SetAttribute("Konstanta", "nema");
			composit->InsertEndChild(operation);
		}
		if (typeid(*o) == typeid(Median)) {
			XMLElement* operation = xmlOperation->NewElement("Medina");
			operation->SetAttribute("Konstanta", "nema");
			composit->InsertEndChild(operation);
		}
		if (typeid(*o) == typeid(CompositOperation)) {
			XMLElement* operation = xmlOperation->NewElement((((CompositOperation*)o)->getName()).c_str());
			operation->SetAttribute("Konstanta", "nema");
			composit->InsertEndChild(operation);
			exportComposit(i, (CompositOperation*)o);
		}
	}
	xmlOperation->SaveFile((comp->getName()).c_str());
}