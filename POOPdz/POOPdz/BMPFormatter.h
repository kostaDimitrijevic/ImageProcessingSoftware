#pragma once
#include"Formatter.h"
#include<cstdint>
#include<fstream>
#include<iostream>
#include<string>

class BMPh: public Formatter{
private:
	unsigned int BMP_size;
	unsigned int width;
	unsigned int height;
	unsigned int BMP_offset;
	std::fstream image;
public:
	Image import(std::string file, Image* i) {
		image.open(file, std::ios::binary | std::ios::in | std::ios::out);

		image.seekg(0x2, std::ios::beg);
		image.read((char*)&BMP_size, sizeof(BMP_size));
		
		image.seekg(0xA, std::ios::beg);
		image.read((char*)&BMP_offset, sizeof(BMP_offset));

		image.seekg(0x12, std::ios::beg);
		image.read((char*)&width, sizeof(width));
		image.read((char*)&height, sizeof(height));

		unsigned char r, g, b, a;
		Layer l(height, width);
		image.seekg(BMP_offset, std::ios::beg);
		for (vector<Pixel> &i : l.getLayer()) {
			for (Pixel &j : i) {
				image.read((char*)&b, sizeof(b));
				image.read((char*)&g, sizeof(g));
				image.read((char*)&r, sizeof(r));
				image.read((char*)&a, sizeof(a));
				j.setRed(r);
				j.setGreen(g);
				j.setBlue(b);
				j.setAlpha(a);
			}
		}
		std::reverse(l.getLayer().begin(), l.getLayer().end());
		//image.close();
		l.setName(file);
		i->addLayer(l);
		image.close();
		return *i;
	}
	void expor(Image& picture, std::string file){
		std::fstream pic;
		pic.open(file, std::ios::binary | std::ios::out);
		#pragma pack(2)
		unsigned char ID[2]{ 0x42, 0x4D };
		uint32_t BMPsize = 122 + picture.getImage().front().getLayer().size() * picture.getImage().front().getLayer()[0].size() * 4;	//size 
		unsigned char offset[8]{
			0x00, 0x00,//Application specific
			0x00, 0x00,// -----//----
			0x7A, 0x00, 0x00, 0x00,// offset for pixel array
		};
			//DIB
		unsigned char DIB_size[4]{ 0x6C, 0x00, 0x00, 0x00, };//Num of the bytes int the DIB header
		uint32_t width = picture.getImage().front().getLayer()[0].size();	//width
		uint32_t height = picture.getImage().front().getLayer().size();	//height
		unsigned char A_Eh[8]{
			0x01, 0x00, //num of color planes being used
			0x20, 0x00, //num of bits per pixel
			0x03, 0x00, 0x00, 0x00, 
		}; //BI_BITFIELDS
		uint32_t rawBitMap = width * height * 4;
		unsigned char DIB[84]{//Size of the raw bitmap data (including padding) TREBA DA SE PROMENII
			0x13, 0x0B, 0x00, 0x00, //Print resolution of the image...
			0x13, 0x0B, 0x00, 0x00, //..
			0x00, 0x00, 0x00, 0x00, //num of collor in the palette
			0x00, 0x00, 0x00, 0x00, //0 means all colors are important
			0x00, 0x00, 0xFF, 0x00, //Red channel bit mask
			0x00, 0xFF, 0x00, 0x00, //Green channel bit mask 
			0xFF, 0x00, 0x00, 0x00, // Blue channel bit mask
			0x00, 0x00, 0x00, 0xFF, //Alpha channel bit mask
			0x20, 0x6E, 0x69, 0x57, //LCS_WINDOWS_COLOR_SPACE
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,//Unused for LCS "Win " or "sRGB"
			0x00, 0x00, 0x00, 0x00, //	Unused for LCS "Win " or "sRGB"
			0x00, 0x00, 0x00, 0x00, //	Unused for LCS "Win " or "sRGB"
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00//	Unused for LCS "Win " or "sRGB"
				//STAR OF THE PIXEL ARRAY
		};
		#pragma pack(1)
		pic.seekp(0x00, std::ios::beg);
		pic.write((char*)&ID, sizeof(ID));
		pic.write((char*)&BMPsize, sizeof(BMPsize));
		pic.write((char*)&offset, sizeof(offset));
		pic.write((char*)&DIB_size, sizeof(DIB_size));
		pic.write((char*)&width, sizeof(width));
		pic.write((char*)&height, sizeof(height));
		pic.write((char*)&A_Eh, sizeof(A_Eh));
		pic.write((char*)&rawBitMap, sizeof(rawBitMap));
		pic.write((char*)&DIB, sizeof(DIB));
		for (Layer& l : picture.getImage()) {
			std::reverse(l.getLayer().begin(), l.getLayer().end());
		}
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
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
				pic.write((char*)&b, sizeof(b));
				pic.write((char*)&g, sizeof(g));
				pic.write((char*)&r, sizeof(r));
				pic.write((char*)&a, sizeof(a));
			}
		}
		pic.close();
	}

};

