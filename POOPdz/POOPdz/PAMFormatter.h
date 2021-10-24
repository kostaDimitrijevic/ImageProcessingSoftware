#pragma once
#include"Formatter.h"
#include<fstream>
#include<string>
class PAMh : public Formatter {
private:
	int width;
	int height;
	std::fstream image;
public:
	Image import(std::string file, Image *i) {
		image.open(file, std::ios::binary | std::ios::in | std::ios::out);
		int a0 = 0, space = 0;
		char c=' ';
		std::string w,h;
		while (space < 2) {
			image.read((char*)&c, sizeof(c));
			if (c == ' ') {
				if (space == 0) {
					while (c != '\n') {
						w = w + c;
						image.read((char*)&c, sizeof(c));
					}
					a0++;
					width = std::stoi(w);
					space++;
					continue;
				}
				if (space == 1) {
					while (c != '\n') {
						h = h + c;
						image.read((char*)&c, sizeof(c));
					}
					a0++;
					height = std::stoi(h);
					space++;
				}
			}
		}
		while (a0 < 6) {
			image.read((char*)&c, sizeof(c));
			if (c == '\n') a0++;
		}
		unsigned char r, g, b, a;
		Layer l(height, width);
		for (vector<Pixel> &i : l.getLayer()) {
			for (Pixel &j : i) {
				image.read((char*)&r, sizeof(r));
				image.read((char*)&g, sizeof(g));
				image.read((char*)&b, sizeof(b));
				image.read((char*)&a, sizeof(a));
				j.setRed(r);
				j.setGreen(g);
				j.setBlue(b);
				j.setAlpha(a);
			}
		}
		l.setName(file);
		i->addLayer(l);
		return *i;
	};
	void expor(Image& picture, std::string file) {
	#pragma pack(2)
		std::fstream pic;
		pic.open(file, std::ios::binary | std::ios::out);
		unsigned char P7[2]{ 'P', '7' };
		unsigned char width[6]{ 'W','I','D','T','H', ' ' };
		unsigned char height[7]{ 'H','E','I','G','H','T',' ' };
		int w = picture.getImage().front().getLayer()[0].size();
		int h = picture.getImage().front().getLayer().size();
		unsigned char depth[7]{ 'D','E','P','T','H',' ','4'};
		unsigned char maxval[10]{ 'M', 'A', 'X', 'V', 'A', 'L', ' ','2', '5' ,'5' };
		unsigned char tupltype[9]{ 'T','U','P','L','T','Y','P','E',' ' };
		unsigned char rgba[9]{ 'R','G','B','_','A','L','P','H','A' };
		unsigned char endhdr[6]{ 'E','N','D','H','D','R' };
		unsigned char nextRow[1]{ '\n' };
		std::string wi = to_string(w);
		std::string he = to_string(h);
		pic.write((char*)&P7, sizeof(P7));
		pic.write((char*)&nextRow, sizeof(nextRow));
		pic.write((char*)&width, sizeof(width));
		for (int i = 0; i < wi.length(); i++) {
			pic.write((char*)&wi[i], sizeof(wi[i]));
		}
		pic.write((char*)&nextRow, sizeof(nextRow));
		pic.write((char*)&height, sizeof(height));
		for (int i = 0; i < he.length(); i++) {
			pic.write((char*)&he[i], sizeof(he[i]));
		}
		pic.write((char*)&nextRow, sizeof(nextRow));
		pic.write((char*)&depth, sizeof(depth));
		pic.write((char*)&nextRow, sizeof(nextRow));
		pic.write((char*)&maxval, sizeof(maxval));
		pic.write((char*)&nextRow, sizeof(nextRow));
		pic.write((char*)&tupltype, sizeof(tupltype));
		pic.write((char*)&rgba, sizeof(rgba));
		pic.write((char*)&nextRow, sizeof(nextRow));
		pic.write((char*)&endhdr, sizeof(endhdr));
		pic.write((char*)&nextRow, sizeof(nextRow));
		//for (Layer& l : picture.getImage()) {
		//	std::reverse(l.getLayer().begin(), l.getLayer().end());
		//}
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				picture.resetRGBA();
				for (Layer& l : picture.getImage()) {
					picture.operationA(l.getLayer()[i][j], l.getTransparency());
					picture.operationRGB(l.getLayer()[i][j], l.getTransparency());
					if (l.getTransparency() == 100)
						break;
				}
				double a1 = picture.getA();
				uint8_t b1 = picture.getB();
				uint8_t r1 = picture.getR();
				uint8_t g1 = picture.getG();
				if (a1 != 0) {
					b1 = b1 / a1;
					b1 = b1 % 256;
					r1 = r1 / a1;
					r1 = r1 % 256;
					g1 = g1 / a1;
					g1 = g1 % 256;
				}
				a1 = a1 * 255;
				unsigned char a = a1;
				unsigned char b = b1;
				unsigned char r = r1;
				unsigned char g = g1;
				pic.write((char*)&r, sizeof(r));
				pic.write((char*)&g, sizeof(g));
				pic.write((char*)&b, sizeof(b));
				pic.write((char*)&a, sizeof(a));
			}
		}
		pic.close();
	};
	#pragma pack(1)
};