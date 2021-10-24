#pragma once
#include"Operation.h"
using namespace std;
class Add : public Operation {
private:
	bool is_in_composit = false;
	Layer* lay;
	int c;
public:
	Add(Layer *l, int val) : lay(l), c(val) {};
	int getC() { return c; }
	void setLayer(Layer *l) { lay = l; };
	void setConstant(int con = 0) { c = con; };
	void setBool(bool b) { is_in_composit = b; }
	void Execute() {
		if (lay->getActivity()) {
			if (!lay->getSelection()) {
				for_each(lay->getLayer().begin(), lay->getLayer().end(), [this, c = getC()](vector<Pixel>& vp) {
					for_each(vp.begin(), vp.end(), [&](Pixel& p) {
						int r = p.getRed(), b = p.getBlue(), g = p.getGreen();
						if (!is_in_composit) {
							r = (r + c) % 256;
							b = (b + c) % 256;
							g = (g + c) % 256;
						}
						else {
							r = (r + c);
							b = (b + c);
							g = (g + c);
						}
						p.setRed(r);
						p.setBlue(b);
						p.setGreen(g);
					});
				});
			}
			else {
				for_each(lay->getLayer().begin(), lay->getLayer().end(), [this, c = getC()](vector<Pixel>& vp) {
					for_each(vp.begin(), vp.end(), [&](Pixel& p) {
						if (p.getSelection()) {
							int r = p.getRed(), b = p.getBlue(), g = p.getGreen();
							if (!is_in_composit) {
								r = (r + c) % 256;
								b = (b + c) % 256;
								g = (g + c) % 256;
							}
							else {
								r = (r + c);
								b = (b + c);
								g = (g + c);
							}
							p.setRed(r);
							p.setBlue(b);
							p.setGreen(g);
						}
					});
				});
			}
		}
	}
};
class Subtraction: public Operation {
private:
	bool is_in_composit=false;
	Layer* lay;
	int c;
public:
	Subtraction(Layer *l, int val) : lay(l), c(val) {};
	int getC() { return c; }
	void setLayer(Layer* l) { lay = l; };
	void setConstant(int con = 0) { c = con; };
	void setBool(bool b) { is_in_composit = b; }
	void Execute() {
		if (lay->getActivity()) {
			if (!lay->getSelection()) {
				for_each(lay->getLayer().begin(), lay->getLayer().end(), [this, c = getC()](vector<Pixel>& vp) {
					for_each(vp.begin(), vp.end(), [&](Pixel& p) {
						int r = p.getRed(), b = p.getBlue(), g = p.getGreen();
						if (!is_in_composit) {
							r = (r - c) % 256;
							b = (b - c) % 256;
							g = (g - c) % 256;
						}
						else {
							r = (r - c);
							b = (b - c);
							g = (g - c);
						}
						p.setRed(r);
						p.setBlue(b);
						p.setGreen(g);
					});
				});
			}
			else {
				for_each(lay->getLayer().begin(), lay->getLayer().end(), [this, c = getC()](vector<Pixel>& vp) {
					for_each(vp.begin(), vp.end(), [&](Pixel& p) {
						if (p.getSelection()) {
							int r = p.getRed(), b = p.getBlue(), g = p.getGreen();
							if (!is_in_composit) {
								r = (r - c) % 256;
								b = (b - c) % 256;
								g = (g - c) % 256;
							}
							else {
								r = (r - c);
								b = (b - c);
								g = (g - c);
							}
							p.setRed(r);
							p.setBlue(b);
							p.setGreen(g);
						}
					});
				});
			}
		}
	}
};

class InvSubtraction: public Operation {
private:
	bool is_in_composit = false;
	Layer* lay;
	int c;
public:
	InvSubtraction(Layer *l, int val) : lay(l), c(val) {};
	int getC() { return c; }
	void setLayer(Layer* l) { lay = l; };
	void setConstant(int con = 0) { c = con; };
	void setBool(bool b) { is_in_composit = b; }
	void Execute() {
		if (lay->getActivity()) {
			if (!lay->getSelection()) {
				for_each(lay->getLayer().begin(), lay->getLayer().end(), [this, c = getC()](vector<Pixel>& vp) {
					for_each(vp.begin(), vp.end(), [&](Pixel& p) {
						int r = p.getRed(), b = p.getBlue(), g = p.getGreen();
						if (!is_in_composit) {
							r = (c - r) % 256;
							b = (c - b) % 256;
							g = (c - g) % 256;
						}
						else {
							r = (c - r);
							b = (c - b);
							g = (c - g);
						}
						p.setRed(r);
						p.setBlue(b);
						p.setGreen(g);
					});
				});
			}
			else {
				for_each(lay->getLayer().begin(), lay->getLayer().end(), [this, c = getC()](vector<Pixel>& vp) {
					for_each(vp.begin(), vp.end(), [&](Pixel& p) {
						if (p.getSelection()) {
							int r = p.getRed(), b = p.getBlue(), g = p.getGreen();
							if (!is_in_composit) {
								r = (c - r) % 256;
								b = (c - b) % 256;
								g = (c - g) % 256;
							}
							else {
								r = (c - r);
								b = (c - b);
								g = (c - g);
							}
							p.setRed(r);
							p.setBlue(b);
							p.setGreen(g);
						}
					});
				});
			}
		}
	}
};

class Multiplication : public Operation {
private:
	bool is_in_composit = false;
	Layer* lay;
	int c;
public:
	Multiplication(Layer *l, int val) : lay(l), c(val) {};
	int getC() { return c; }
	void setLayer(Layer* l) { lay = l; };
	void setConstant(int con = 0) { c = con; };
	void setBool(bool b) { is_in_composit = b; }
	void Execute() {
		if (lay->getActivity()) {
			if (!lay->getSelection()) {
				for_each(lay->getLayer().begin(), lay->getLayer().end(), [this, c = getC()](vector<Pixel>& vp) {
					for_each(vp.begin(), vp.end(), [&](Pixel& p) {
						int r = p.getRed(), b = p.getBlue(), g = p.getGreen();
						if (!is_in_composit) {
							r = (r * c) % 256;
							b = (b * c) % 256;
							g = (g * c) % 256;
						}
						else {
							r = (r * c);
							b = (b * c);
							g = (g * c);
						}
						p.setRed(r);
						p.setBlue(b);
						p.setGreen(g);
					});
				});
			}
			else {
				for_each(lay->getLayer().begin(), lay->getLayer().end(), [this, c = getC()](vector<Pixel>& vp) {
					for_each(vp.begin(), vp.end(), [&](Pixel& p) {
						if (p.getSelection()) {
							int r = p.getRed(), b = p.getBlue(), g = p.getGreen();
							if (!is_in_composit) {
								r = (r * c) % 256;
								b = (b * c) % 256;
								g = (g * c) % 256;
							}
							else {
								r = (r * c);
								b = (b * c);
								g = (g * c);
							}
							p.setRed(r);
							p.setBlue(b);
							p.setGreen(g);
							p.minusSelection();
						}
					});
				});
			}
		}
	}
};

class Divide : public Operation {
private:
	Layer* lay;
	int c;
public:
	Divide(Layer *l, int val) : lay(l), c(val) {};
	int getC() { return c; }
	void setBool(bool b) {};
	void setLayer(Layer* l) { lay = l; };
	void setConstant(int con = 0) { c = con; };
	void Execute() {
		if (lay->getActivity()) {
			if (!lay->getSelection()) {
				for_each(lay->getLayer().begin(), lay->getLayer().end(), [this, c = getC()](vector<Pixel>& vp) {
					for_each(vp.begin(), vp.end(), [&](Pixel& p) {
						int r = p.getRed(), b = p.getBlue(), g = p.getGreen();
						r = r / c;
						b = b / c;
						g = g / c;
						p.setRed(r);
						p.setBlue(b);
						p.setGreen(g);
					});
				});
			}
			else {
				for_each(lay->getLayer().begin(), lay->getLayer().end(), [this, c = getC()](vector<Pixel>& vp) {
					for_each(vp.begin(), vp.end(), [&](Pixel& p) {
						if (p.getSelection()) {
							int r = p.getRed(), b = p.getBlue(), g = p.getGreen();
							r = r / c;
							b = b / c;
							g = g / c;
							p.setRed(r);
							p.setBlue(b);
							p.setGreen(g);
						}
					});
				});
			}
		}
	}
};

class InvDivide : public Operation {
private:
	bool is_in_composit = false;
	Layer* lay;
	int c;
public:
	InvDivide(Layer *l, int val) : lay(l), c(val) {};
	int getC() { return c; }
	void setLayer(Layer* l) { lay = l; };
	void setConstant(int con = 0) { c = con; };
	void setBool(bool b) { is_in_composit = b; }
	void Execute() {
		if (lay->getActivity()) {
			if (!lay->getSelection()) {
				for_each(lay->getLayer().begin(), lay->getLayer().end(), [this, c = getC()](vector<Pixel>& vp) {
					for_each(vp.begin(), vp.end(), [&](Pixel& p) {
						int r = p.getRed(), b = p.getBlue(), g = p.getGreen();
						if (!is_in_composit) {
							r = (c / r) % 256;
							b = (c / b) % 256;
							g = (c / g) % 256;
						}
						else {
							r = (c / r);
							b = (c / b);
							g = (c / g);
						}
						p.setRed(r);
						p.setBlue(b);
						p.setGreen(g);
					});
				});
			}
			else {
				for_each(lay->getLayer().begin(), lay->getLayer().end(), [this, c = getC()](vector<Pixel>& vp) {
					for_each(vp.begin(), vp.end(), [&](Pixel& p) {
						if (p.getSelection()) {
							int r = p.getRed(), b = p.getBlue(), g = p.getGreen();
							if (!is_in_composit) {
								r = (c / r) % 256;
								b = (c / b) % 256;
								g = (c / g) % 256;
							}
							else {
								r = (c / r);
								b = (c / b);
								g = (c / g);
							}
							p.setRed(r);
							p.setBlue(b);
							p.setGreen(g);
						}
					});
				});
			}
		}
	}
};

class Power : public Operation {
private:
	bool is_in_composit = false;
	Layer* lay;
	int c;
public:
	Power(Layer *l, int val) : lay(l), c(val) {};
	int getC() { return c; }
	void setLayer(Layer* l) { lay = l; };
	void setConstant(int con = 0) { c = con; };
	void setBool(bool b) { is_in_composit = b; }
	void Execute() {
		if (lay->getActivity()) {
			if (!lay->getSelection()) {
				for_each(lay->getLayer().begin(), lay->getLayer().end(), [this, c = getC()](vector<Pixel>& vp) {
					for_each(vp.begin(), vp.end(), [&](Pixel& p) {
						int r = p.getRed(), b = p.getBlue(), g = p.getGreen();
						if (!is_in_composit) {
							r = pow(r, c);
							r = r % 256;
							b = pow(b, c);
							b = b % 256;
							g = pow(g, c);
							g = g % 256;
						}
						else {
							r = pow(r, c);
							b = pow(b, c);
							g = pow(g, c);
						}
						p.setRed(r);
						p.setBlue(b);
						p.setGreen(g);
					});
				});
			}
			else {
				for_each(lay->getLayer().begin(), lay->getLayer().end(), [this, c = getC()](vector<Pixel>& vp) {
					for_each(vp.begin(), vp.end(), [&](Pixel& p) {
						if (p.getSelection()) {
							int r = p.getRed(), b = p.getBlue(), g = p.getGreen();
							if (!is_in_composit) {
								r = pow(r, c);
								r = r % 256;
								b = pow(b, c);
								b = b % 256;
								g = pow(g, c);
								g = g % 256;
							}
							else {
								r = pow(r, c);
								b = pow(b, c);
								g = pow(g, c);
							}
							p.setRed(r);
							p.setBlue(b);
							p.setGreen(g);
						}
					});
				});
			}
		}
	}
};

class Log : public Operation {
private:
	Layer* lay;
	int c;
public:
	Log(Layer *l, int val) : lay(l), c(val) {};
	int getC() { return c; }
	void setBool(bool b) {};
	void setLayer(Layer* l) { lay = l; };
	void setConstant(int con = 0) { c = con; };
	void Execute() {
		if (lay->getActivity()) {
			if (!lay->getSelection()) {
				for_each(lay->getLayer().begin(), lay->getLayer().end(), [this, c = getC()](vector<Pixel>& vp) {
					for_each(vp.begin(), vp.end(), [&](Pixel& p) {
						int r = p.getRed(), b = p.getBlue(), g = p.getGreen();
						r = log(r);
						b = log(b);
						g = log(g);
						p.setRed(r);
						p.setBlue(b);
						p.setGreen(g);
					});
				});
			}
			else {
				for_each(lay->getLayer().begin(), lay->getLayer().end(), [this, c = getC()](vector<Pixel>& vp) {
					for_each(vp.begin(), vp.end(), [&](Pixel& p) {
						if (p.getSelection()) {
							int r = p.getRed(), b = p.getBlue(), g = p.getGreen();
							r = log(r);
							b = log(b);
							g = log(g);
							p.setRed(r);
							p.setBlue(b);
							p.setGreen(g);
						}
					});
				});
			}
		}
	}
};

class Abs : public Operation {
private:
	bool is_in_composit = false;
	Layer* lay;
	int c;
public:
	Abs(Layer *l, int val) : lay(l), c(val) {};
	int getC() { return c; }
	void setLayer(Layer* l) { lay = l; };
	void setConstant(int con = 0) { c = con; };
	void setBool(bool b) { is_in_composit = b; }
	void Execute() {
		if (lay->getActivity()) {
			if (!lay->getSelection()) {
				for_each(lay->getLayer().begin(), lay->getLayer().end(), [this, c = getC()](vector<Pixel>& vp) {
					for_each(vp.begin(), vp.end(), [&](Pixel& p) {
						int r = p.getRed(), b = p.getBlue(), g = p.getGreen();
						if (!is_in_composit) {
							r = abs(r) % 256;
							b = abs(b) % 256;
							g = abs(g) % 256;
						}
						else {
							r = abs(r);
							b = abs(b);
							g = abs(g);
						}
						p.setRed(r);
						p.setBlue(b);
						p.setGreen(g);
					});
				});
			}
			else {
				for_each(lay->getLayer().begin(), lay->getLayer().end(), [this, c = getC()](vector<Pixel>& vp) {
					for_each(vp.begin(), vp.end(), [&](Pixel& p) {
						if (p.getSelection()) {
							int r = p.getRed(), b = p.getBlue(), g = p.getGreen();
							if (!is_in_composit) {
								r = abs(r) % 256;
								b = abs(b) % 256;
								g = abs(g) % 256;
							}
							else {
								r = abs(r);
								b = abs(b);
								g = abs(g);
							}
							p.setRed(r);
							p.setBlue(b);
							p.setGreen(g);
						}
					});
				});
			}
		}
	}
};

class Min : public Operation {
private:
	Layer* lay;
	int c;
public:
	Min(Layer *l, int val) : lay(l), c(val) {};
	int getC() { return c; }
	void setBool(bool b) {};
	void setLayer(Layer* l) { lay = l; };
	void setConstant(int con = 0) { c = con; };
	void Execute() {
		if (lay->getActivity()) {
			if (!lay->getSelection()) {
				for_each(lay->getLayer().begin(), lay->getLayer().end(), [this, c = getC()](vector<Pixel>& vp) {
					for_each(vp.begin(), vp.end(), [&](Pixel& p) {
						int r = p.getRed(), b = p.getBlue(), g = p.getGreen();
						if (r > c) {
							r = c;
						}
						if (g > c) {
							g = c;
						}
						if (b > c) {
							b = c;
						}
						p.setRed(r);
						p.setBlue(b);
						p.setGreen(g);
					});
				});
			}
			else {
				for_each(lay->getLayer().begin(), lay->getLayer().end(), [this, c = getC()](vector<Pixel>& vp) {
					for_each(vp.begin(), vp.end(), [&](Pixel& p) {
						if (p.getSelection()) {
							int r = p.getRed(), b = p.getBlue(), g = p.getGreen();
							if (r > c) {
								r = c;
							}
							if (g > c) {
								g = c;
							}
							if (b > c) {
								b = c;
							}
							p.setRed(r);
							p.setBlue(b);
							p.setGreen(g);
						}
					});
				});
			}
		}
	}
};

class Max : public Operation {
private:
	Layer* lay;
	int c;
public:
	Max(Layer *l, int val) : lay(l), c(val) {};
	int getC() { return c; }
	void setBool(bool b) {};
	void setLayer(Layer* l) { lay = l; };
	void setConstant(int con = 0) { c = con; };
	void Execute() {
		if (lay->getActivity()) {
			if (!lay->getSelection()) {
				for_each(lay->getLayer().begin(), lay->getLayer().end(), [this, c = getC()](vector<Pixel>& vp) {
					for_each(vp.begin(), vp.end(), [&](Pixel& p) {
						int r = p.getRed(), b = p.getBlue(), g = p.getGreen();
						if (r < c) {
							r = c;
						}
						if (g < c) {
							g = c;
						}
						if (b < c) {
							b = c;
						}
						p.setRed(r);
						p.setBlue(b);
						p.setGreen(g);
					});
				});
			}
			else {
				for_each(lay->getLayer().begin(), lay->getLayer().end(), [this, c = getC()](vector<Pixel>& vp) {
					for_each(vp.begin(), vp.end(), [&](Pixel& p) {
						if (p.getSelection()) {
							int r = p.getRed(), b = p.getBlue(), g = p.getGreen();
							if (r < c) {
								r = c;
							}
							if (g < c) {
								g = c;
							}
							if (b < c) {
								b = c;
							}
							p.setRed(r);
							p.setBlue(b);
							p.setGreen(g);
						}
					});
				});
			}
		}
	}
};

class Inversion :public Operation {
private:
	bool is_in_composit;
	Layer* lay;
	int getC() { return 1; }
	void setConstant(int con = 0) {};
public:
	Inversion(Layer* l) :lay(l) {};
	void setLayer(Layer* l) { lay = l; };
	void setBool(bool b) { is_in_composit = b; }
	void Execute() {
		if (lay->getActivity()) {
			if (!lay->getSelection()) {
				for_each(lay->getLayer().begin(), lay->getLayer().end(), [this](vector<Pixel>& vp) {
					for_each(vp.begin(), vp.end(), [&](Pixel& p) {
						int r = p.getRed(), b = p.getBlue(), g = p.getGreen();
						if (!is_in_composit) {
							r = (abs(255 - r)) % 256;
							b = (abs(255 - b)) % 256;
							g = (abs(255 - g)) % 256;
						}
						else {
							r = 255 - r;
							b = 255 - b;
							g = 255 - g;
						}
						p.setRed(r);
						p.setBlue(b);
						p.setGreen(g);
					});
				});
			}
			else {
				for_each(lay->getLayer().begin(), lay->getLayer().end(), [this](vector<Pixel>& vp) {
					for_each(vp.begin(), vp.end(), [&](Pixel& p) {
						if (p.getSelection()) {
							int r = p.getRed(), b = p.getBlue(), g = p.getGreen();
							if (!is_in_composit) {
								r = (abs(255 - r)) % 256;
								b = (abs(255 - b)) % 256;
								g = (abs(255 - g)) % 256;
							}
							else {
								r = 255 - r;
								b = 255 - b;
								g = 255 - g;
							}
							p.setRed(r);
							p.setBlue(b);
							p.setGreen(g);
						}
					});
				});
			}
		}
	}
};
class Grey : public Operation {
private:
	Layer* lay;
	bool is_in_composit = false;
	int getC() { return 1; }
	void setConstant(int con = 0) {};
public:
	Grey(Layer* l) : lay(l) {};
	void setLayer(Layer* l) { lay = l; };
	void setBool(bool b) { is_in_composit = b; }
	void Execute() {
		if (lay->getActivity()) {
			if (!lay->getSelection()) {
				for_each(lay->getLayer().begin(), lay->getLayer().end(), [this](vector<Pixel>& vp) {
					for_each(vp.begin(), vp.end(), [&](Pixel& p) {
						int r = p.getRed(), b = p.getBlue(), g = p.getGreen();
						double ars = 0;
						ars = (r + b + g) / 3;
						r = g = b = ars;
						if (!is_in_composit) {
							r = r % 256;
							g = b = r;
						}
						p.setRed(r);
						p.setBlue(b);
						p.setGreen(g);
					});
				});
			}
			else {
				for_each(lay->getLayer().begin(), lay->getLayer().end(), [this](vector<Pixel>& vp) {
					for_each(vp.begin(), vp.end(), [&](Pixel& p) {
						if (p.getSelection()) {
							int r = p.getRed(), b = p.getBlue(), g = p.getGreen();
							double ars = 0;
							ars = (r + b + g) / 3;
							r = g = b = ars;
							if (!is_in_composit) {
								r = r % 256;
								g = b = r;
							}
							p.setRed(r);
							p.setBlue(b);
							p.setGreen(g);
						}
					});
				});
			}
		}
	}
};

class Black_and_white :public Operation {
private:
	Layer* lay;
	bool is_in_composit = false;
	int getC() { return 1; }
	void setConstant(int con = 0) {};
public:
	Black_and_white(Layer* l) : lay(l) {};
	void setLayer(Layer* l) { lay = l; };
	void setBool(bool b) { is_in_composit = b; }
	void Execute() {
		if (lay->getActivity()) {
			if (!lay->getSelection()) {
				for_each(lay->getLayer().begin(), lay->getLayer().end(), [this](vector<Pixel>& vp) {
					for_each(vp.begin(), vp.end(), [&](Pixel& p) {
						int r = p.getRed(), b = p.getBlue(), g = p.getGreen();
						double ars = 0;
						ars = (r + b + g) / 3;
						if (ars > 127) {
							p.setRed(255);
							p.setBlue(255);
							p.setGreen(255);
						}
						else {
							p.setRed(0);
							p.setBlue(0);
							p.setGreen(0);
						}
					});
				});
			}
			else {
				for_each(lay->getLayer().begin(), lay->getLayer().end(), [this](vector<Pixel>& vp) {
					for_each(vp.begin(), vp.end(), [&](Pixel& p) {
						if (p.getSelection()) {
							int r = p.getRed(), b = p.getBlue(), g = p.getGreen();
							double ars = 0;
							ars = (r + b + g) / 3;
							if (ars > 127) {
								p.setRed(255);
								p.setBlue(255);
								p.setGreen(255);
							}
							else {
								p.setRed(0);
								p.setBlue(0);
								p.setGreen(0);
							}
						}
					});
				});
			}
		}
	}
};
class Median : public Operation {
private:
	Layer* lay;
	int getC() { return 1; }
	void setConstant(int con = 0) {};
public:
	Median(Layer* l) :lay(l) {};
	void setLayer(Layer* l) { lay = l; };
	void setBool(bool b) {};
	void Execute() {
		if (lay->getActivity()) {
			if (!lay->getSelection()) {
				vector<int> greens;
				vector<int> reds;
				vector<int> blues;
				for (int i = 0; i < lay->getLayer().size(); i++) {
					for (int j = 0; j < lay->getLayer()[0].size(); j++) {
						reds.push_back(lay->getLayer()[i][j].getRed());
						if (j + 1 <= lay->getLayer()[0].size())
							reds.push_back(lay->getLayer()[i][j + 1].getRed());
						if (j - 1 >= 0)
							reds.push_back(lay->getLayer()[i][j - 1].getRed());
						if (i + 1 >= 0)
							reds.push_back(lay->getLayer()[i + 1][j].getRed());
						if (i - 1 <= lay->getLayer().size())
							reds.push_back(lay->getLayer()[i - 1][j].getRed());
						lay->getLayer()[i][j].setRed(lay->median(reds));
						blues.push_back(lay->getLayer()[i][j].getBlue());
						if (j + 1 <= lay->getLayer()[0].size())
							blues.push_back(lay->getLayer()[i][j + 1].getBlue());
						if (j - 1 >= 0)
							blues.push_back(lay->getLayer()[i][j - 1].getBlue());
						if (i + 1 >= 0)
							blues.push_back(lay->getLayer()[i + 1][j].getBlue());
						if (i - 1 <= lay->getLayer().size())
							blues.push_back(lay->getLayer()[i - 1][j].getBlue());
						lay->getLayer()[i][j].setBlue(lay->median(blues));
						greens.push_back(lay->getLayer()[i][j].getGreen());
						if (j + 1 <= lay->getLayer()[0].size())
							greens.push_back(lay->getLayer()[i][j + 1].getGreen());
						if (j - 1 >= 0)
							greens.push_back(lay->getLayer()[i][j - 1].getGreen());
						if (i + 1 >= 0)
							greens.push_back(lay->getLayer()[i + 1][j].getGreen());
						if (i - 1 <= lay->getLayer().size())
							greens.push_back(lay->getLayer()[i - 1][j].getGreen());
						lay->getLayer()[i][j].setGreen(lay->median(greens));
						reds.clear();
						blues.clear();
						greens.clear();
					}
				}
			}
		}
	}
};