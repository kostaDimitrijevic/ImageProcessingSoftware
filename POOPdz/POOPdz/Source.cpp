#include<iostream>
#include"Layer.h"
#include "BasicOperation.h"
#include "CompositOperation.h"
#include "BMPFormatter.h"
#include "Image.h"
#include "Selection.h"
#include "Formatter.h"
#include "PAMFormatter.h"
#include "XMLFormatter.h"
using namespace std;
int main(int argc, char* argv[]) {
	int br;
	Image i;
	Formatter *formBMP = new BMPh;
	Formatter *formPAM = new PAMh;
	XMLh *formXML = new XMLh;
	if (argc < 2) {
		while (1) {
			std::cout << "Izaberite stavku koju zelite da izvrsite: \n1.Napravi novi lejer zadavanjem putanje do slike.\n";
			std::cout << "2.Pravljenje prvog lejera zadavanjem putanje do slike i njegovim dimenzijama.\n";
			std::cout << "3.Unos vidljivosti vaseg sloja.\n";
			std::cout << "4.Izvrsavanje pojedinacne operacija nad slikom (ukoliko ste selektovali neke piksele, operacije se izvrsavaju nad njima).\n";
			std::cout << "5.Pravljenje kompozitne operacije (ukoliko ste selektovali neke piksele, operacije se izvrsavaju nad njima).\n";
			std::cout << "6.Importovanje kompozitne funkcije.\n";
			std::cout << "7.Napravi selekciju nad slikom.\n";
			std::cout << "8.Izvrsavanje kompozitne operacije.\n";
			std::cout << "9.Eksporovanje vase slike.\n";
			std::cout << "10.Eksportovanje kompozitne funkcije.\n";
			std::cout << "11.Brisanje lejera.\n";
			std::cout << "12.kraj.\n";
			std::cout << "Uneti broj: \n";
			std::cin >> br;
			if (br == 1) {
				std::system("cls");
				int f;
				std::cout << "Izaberite format:\n 1.BMP\n 2.PAM\n 3.XML\n";
				std::cout << "Unesite broj: ";
				std::cin >> f;
				std::cout << std::endl;
				if (f == 1) { //PRAVLJENJE BMP
					std::cout << "Uneti putanju slike: ";
					std::string name;
					std::cin >> name;
					std::cout << std::endl;					
					i = formBMP->import(name, &i);
				}
				if (f == 2) {//PRAVLJENJE PAM
					std::cout << "Uneti putanju slike: ";
					std::string name;
					std::cin >> name;
					std::cout << std::endl;
					i = formPAM->import(name, &i);
				}
				if (f == 3) {
					std::cout << "Uneti putanju slike: ";
					std::string name;
					std::cin >> name;
					std::cout << std::endl;
					i = formXML->import(name, &i);
				}
			}
			if (br == 2) {
				std::system("cls");
				int f, x, y;
				std::cout << "Izaberite format:\n 1.BMP\n 2.PAM\n 3.XML\n";
				std::cout << "Unesite broj: ";
				std::cin >> f;
				std::cout << std::endl;
				std::cout << "Unesite duzinu i sirinu zeljenog lejera: ";
				std::cin >> x >> y;
				std::cout << std::endl;
				Layer help(x, y);
				if (f == 1) { //PRAVLJENJE BMP
					std::cout << "Uneti putanju slike: ";
					std::string name;
					std::cin >> name;
					std::cout << std::endl;
					i = formBMP->import(name, &i);
					if (i.getImage().front().getLayer().size() < help.getLayer().size() && i.getImage().front().getLayer()[0].size() > help.getLayer()[0].size()) {
						i.getImage().front().extendLayerY(i.getImage().front(), help);
					}
					if (i.getImage().front().getLayer().size() > help.getLayer().size() && i.getImage().front().getLayer()[0].size() < help.getLayer()[0].size()) {
						i.getImage().front().extendLayerX(i.getImage().front(), help);
					}
					if (i.getImage().front().getLayer().size() < help.getLayer().size() && i.getImage().front().getLayer()[0].size() < help.getLayer()[0].size()) {
						i.getImage().front().extendLayerX(i.getImage().front(), help);
						i.getImage().front().extendLayerY(i.getImage().front(), help);
					}
				}
				if (f == 2) {//PRAVLJENJE PAM
					std::cout << "Uneti putanju slike: ";
					std::string name;
					std::cin >> name;
					std::cout << std::endl;
					i = formPAM->import(name, &i);
					if (i.getImage().front().getLayer().size() < help.getLayer().size() && i.getImage().front().getLayer()[0].size() > help.getLayer()[0].size()) {
						i.getImage().front().extendLayerY(i.getImage().front(), help);
					}
					if (i.getImage().front().getLayer().size() > help.getLayer().size() && i.getImage().front().getLayer()[0].size() < help.getLayer()[0].size()) {
						i.getImage().front().extendLayerX(i.getImage().front(), help);
					}
					if (i.getImage().front().getLayer().size() < help.getLayer().size() && i.getImage().front().getLayer()[0].size() < help.getLayer()[0].size()) {
						i.getImage().front().extendLayerX(i.getImage().front(), help);
						i.getImage().front().extendLayerY(i.getImage().front(), help);
					}
				}
				if (f == 3) {
					std::cout << "Uneti putanju slike: ";
					std::string name;
					std::cin >> name;
					std::cout << std::endl;
					i = formXML->import(name, &i);
					if (i.getImage().front().getLayer().size() < help.getLayer().size() && i.getImage().front().getLayer()[0].size() > help.getLayer()[0].size()) {
						i.getImage().front().extendLayerY(i.getImage().front(), help);
					}
					if (i.getImage().front().getLayer().size() > help.getLayer().size() && i.getImage().front().getLayer()[0].size() < help.getLayer()[0].size()) {
						i.getImage().front().extendLayerX(i.getImage().front(), help);
					}
					if (i.getImage().front().getLayer().size() < help.getLayer().size() && i.getImage().front().getLayer()[0].size() < help.getLayer()[0].size()) {
						i.getImage().front().extendLayerX(i.getImage().front(), help);
						i.getImage().front().extendLayerY(i.getImage().front(), help);
					}
				}
			}
			if (br == 3) {
				std::system("cls");
				std::cout << "Unesite ime slike ciju vidljivost zelite da namestite: ";
				std::string name;
				std::cin >> name;
				bool flag = false;
			std:cout << std::endl;
				for (Layer&l : i.getImage()) {
					if (l.getName() == name) {
						std::cout << "Unesite vidljivost od 0-100 (0-potpuno providan): ";
						int t;
						std::cin >> t;
						std::cout << std::endl;
						l.setTransparency(t);
						flag = true;
					}
				}
				if(!flag)std::cout << "Lose uneto ime";
			}
			if (br == 4) {
				std::string operation;
				int c;
				std::system("cls");
				while (1) {
					std::cout << "Moguce operacije (uneti kraj za prekid): \n";
					std::cout << "1.Add\n2.Subtaction\n3.Inverted subtraction\n4.Multiplication\n5.Divide\n6.Inverted division\n7.Power\n";
					std::cout << "8.Log\n9.Absolute\n10.Minimum\n11.Maximum\n12.Inversion\n13.Grey\n14.Black and white\n15.Median\n16.kraj.\n";
					std::cout << "Uneti tacan naziv operacije koju zelite da izvrsite (uneti kraj za prekid): " << std::endl;
					getchar();
					getline(std::cin, operation);
					if (operation == "kraj") break;
					std::cout << "Zatim uneti konstantu sa kojom zelite da se operacija izvrsava: ";
					std::cin >> c;
					Operation* o = i.takeOperation(operation);
					if (o == nullptr) {
						std::cout << "Lose uneto ime operacije!";
						continue;
					}
					i.doOperation(o, c);
					std::system("cls");
				}
			}
			if (br == 5) {
				vector<Operation*> oper;
				int c;
				Operation* o = nullptr;
				std::string name, operation;
				std::system("cls");
				std::cout << "Dati naziv kompozitnoj funkciji: ";
				std::cin >> name;
				std::cout << std::endl;
				std::cout << "Moguce operacije (uneti kraj za prekid), ukoliko zelite da ubacite kompozitnu unesite ime kompozitne: \n";
				std::cout << "1.Add\n2.Subtaction\n3.Inverted subtraction\n4.Multiplication\n5.Divide\n6.Inverted division\n7.Power\n";
				std::cout << "8.Log\n9.Absolute\n10.Minimum\n11.Maximum\n12.Inversion\n13.Grey\n14.Black and white\n15.Median\n16.kraj\n";
				while (1) {
					std::cout << "Uneti tacan naziv operacije koju zelite da izvrsite (uneti kraj za prekid): " << std::endl;
					std::cin >> operation;
					if (operation == "kraj") break;
					std::cout << std::endl;
					o = i.takeOperation(operation);
					if (o == nullptr) {
						o = i.takeFromCompositVector(operation);
						if (o == nullptr) {
							std::cout << "Lose uneto ime operacije!";
							continue;
						}
					}
					else {
						std::cout << "Zatim uneti konstantu sa kojom zelite da se operacija izvrsava: ";
						std::cin >> c;
						o->setConstant(c);
					}
					oper.push_back(o);
				}
				Layer temp(1, 1);
				Operation* composit = new CompositOperation(oper, &temp, name);
				i.addToCompositVector((CompositOperation*)composit);
				i.doCompositOperation(composit);
				std::system("cls");
			}
			if (br == 6) {
				std::string name;
				std::system("cls");
				std::cout << "Unesite ime fajla u kome je zapisana vasa kompozitna funkcija: ";
				std::cin >> name;
				std::cout << std::endl;
				Operation* comp = ((XMLh*)formXML)->importComposit(name + ".fun", &i);
				i.doCompositOperation(comp);
			}
			if (br == 7) {
				int x, y , width, height;
				std::string name;
				std::system("cls");
				std::cout << "Unesite ime vase selekcije: ";
				std::cin >> name;
				std::cout << std::endl;
				Selection s(name, true);
				std::cout << "Uneti koordinate na kojima ce poceti vasa selekcija (u odnosu na gornji levi ugao slike): ";
				std::cin >> x >> y;
				std::cout << std::endl;
				std::cout << "Uneti duzinu i sirinu vase selekcije:";
				std::cin >> width >> height;
				s.AddRectangle(x, y, height, width);
				std::cout << std::endl;
				i.addSelectionToMap(name, s);
				i.select(name);
				for (Layer l : i.getImage()) {
					l.setSelection();
				}
			}
			if (br == 8) {
				std::system("cls");
				std::string name;
				std::cout << "Unesite ime kompozitne operacije koju zelite da izvrsite: ";
				std::cin >> name;
				std::cout << std::endl;
				for (CompositOperation* comp : i.getComposit_vector()) {
					if (comp->getName() == name) {
						i.doCompositOperation(comp);
						break;
					}
				}
			}
			if (br == 9) {
				std::system("cls");
				int f;
				std::string file;
				std::cout << "Izaberite format:\n 1.BMP\n 2.PAM\n 3.XML\n";
				std::cout << "Unesite broj: ";
				std::cin >> f;
				std::cout << std::endl;
				std::cout << "Unesite ime fajla gde zelite da sacuvate vasu sliku: ";
				std::cin >> file;
				std::cout << std::endl;
				if (f == 1) {
					formBMP->expor(i, file);
					std::cout << "Vas fajl je sacuvan!\n";
				}
				if (f == 2) {
					formPAM->expor(i, file);
					std::cout << "Vas fajl je sacuvan!\n";
				}
				if (f == 3) {
					formXML->expor(i, file);
					std::cout << "Vas fajl je sacuvan!\n";
				}
			}
			if (br == 10) {
				std::system("cls");
				bool flag=false;
				std::string name;
				std::cout << "Unesite ime kompozitne funkcije koju zelite da sacuvate: ";
				std::cin >> name;
				std::cout << std::endl;
				for (CompositOperation* comp : i.getComposit_vector()) {
					if (comp->getName() == name) {
						((XMLh*)formXML)->exportComposit(i, comp);
						std::cout << "Vas fajl je sacuvan!\n";
						flag = true;
						break;
					}
				}
				if (!flag) std::cout << "Lose uneto ime funkcije!\n";
			}
			if (br == 11) {
				std::system("cls");
				std::cout << "Unesite ime lejera kojeg zelite da obrisete: ";
				std::string name;
				std::cin >> name;
				std::cout << std::endl;
				for (Layer& l : i.getImage()) {
					if (l.getName() == name) {
						i.deleteLayer(l);
						break;
					}
				}
			}
			if (br == 12) {
				break;
			}
			/*else {
				std::cout << "Lose unet broj!\n";
				continue;
			}*/

		}
	}
	else {
		i = formXML->import(argv[1], &i);
		Operation* comp = formXML->importComposit(argv[2], &i);
		i.doCompositOperation((CompositOperation*)comp);
		formXML->expor(i, argv[1]);
		formXML->exportComposit(i, (CompositOperation*)comp);
	}
}