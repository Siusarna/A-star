#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include "a-star.hpp"
#include <Windows.h>

using namespace std;

enum City {
	Сoфія, Самоков, Дупница, Пернік, Пловдив, Троян, Ямбол, Єлхово,
	Кирджалі, Карлово, Варна, Шумен, Плевен, Слівен, Русе
};

std::ostream& operator<<(std::ostream& os, const City& a) {
	std::string out;
	switch (a) {
	case Сoфія: out = "Софія"; break;
	case Самоков: out = "Самоков"; break;
	case Дупница: out = "Дупница"; break;
	case Пернік: out = "Пернік"; break;
	case Пловдив: out = "Пловдив"; break;
	case Троян: out = "Троян"; break;
	case Ямбол: out = "Ямбол"; break;
	case Єлхово: out = "Єлхово"; break;
	case Кирджалі: out = "Кирджалі"; break;
	case Карлово: out = "Карлово"; break;
	case Варна: out = "Варна"; break;
	case Шумен: out = "Шумен"; break;
	case Плевен: out = "Плевен"; break;
	case Слівен: out = "Слівен"; break;
	case Русе: out = "Русе"; break;
	}
	return os << out;
}

using Dollars = double;

Dollars **createMatrix(Dollars **&sw) {
	Dollars **routes = new Dollars*[15];
	for (int i = 0; i < 15; i++) {
		routes[i] = new Dollars[15];
		for (int j = 0; j < 15; j++) {
			routes[i][j] = 0;
		}
	}
	routes[0][1] = 57; routes[0][2] = 67;  routes[0][3] = 35;  routes[0][4] = 143;  routes[0][9] = 139;
	routes[1][2] = 40; routes[1][4] = 145;  routes[2][3] = 49;  routes[4][5] = 125;
	routes[4][6] = 168;  routes[4][8] = 95;  routes[4][9] = 60; routes[5][9] = 69;
	routes[5][12] = 70; routes[6][7] = 38; routes[6][13] = 28;  routes[7][11] = 167;
	routes[7][13] = 68;  routes[8][9] = 190;  routes[9][12] = 140; routes[9][13] = 140;
	routes[10][11] = 88;  routes[10][12] = 300; routes[10][14] = 215;  routes[11][14] = 111;
	routes[12][14] = 151;  routes[13][14] = 211;

	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (routes[i][j] != 0) routes[j][i] = routes[i][j];
			sw[i][j] = 0;
		}
	}
	
	sw[0][5] = 166; sw[0][6] = 300; sw[0][7] = 327; sw[0][8] = 244; sw[0][10] = 469;
	sw[0][11] = 384; sw[0][12] = 169; sw[0][13] = 279; sw[0][14] = 313; sw[1][3] = 65.8;
	sw[1][5] = 189; sw[1][6] = 281; sw[1][7] = 293; sw[1][8] = 210; sw[1][9] = 120;
	sw[1][10] = 458; sw[1][11] = 403; sw[1][12] = 212; sw[1][13] = 271; sw[1][14] = 355;
	sw[2][4] = 155; sw[2][5] = 229; sw[2][6] = 321; sw[2][7] = 333; sw[2][8] = 250;
	sw[2][9] = 201; sw[2][10] = 498; sw[2][11] = 443; sw[2][12] = 235; sw[2][13] = 311;
	sw[2][14] = 79; sw[3][4] = 174; sw[3][5] = 194; sw[3][6] = 328; sw[3][7] = 351;
	sw[3][8] = 268; sw[3][9] = 169; sw[3][10] = 483; sw[3][11] = 397; sw[3][12] = 197;
	sw[3][13] = 402; sw[3][14] = 349; sw[4][7] = 179; sw[4][10] = 344; sw[4][11] = 290;
	sw[4][12] = 194; sw[4][13] = 158; sw[4][14] = 276; sw[5][6] = 201; sw[5][7] = 232;
	sw[5][8] = 210; sw[5][10] = 312; sw[5][11] = 226; sw[5][13] = 180; sw[5][14] = 183;
	sw[6][8] = 167; sw[6][9] = 160;  sw[6][10] = 184; sw[6][11] = 129; sw[6][12] = 240;
	sw[6][14] = 212; sw[7][8] = 142;  sw[7][9] = 189; sw[7][10] = 222; sw[7][12] = 266;
	sw[7][14] = 248; sw[8][10] = 351; sw[8][10] = 351; sw[8][11] = 296; sw[8][12] = 274;
	sw[8][13] = 170; sw[8][14] = 309; sw[9][10] = 362; sw[9][11] = 261; sw[9][14] = 228;
	sw[10][13] = 190; sw[11][12] = 215; sw[11][13] = 127; sw[12][13] = 214;
	
	for (int i = 0; i < 15; i++) {
		for (int j = i; j < 15; j++) {
			if (sw[i][j] == 0) {
				sw[i][j] = routes[i][j];
				sw[j][i] = routes[i][j];
			}
			else {
				sw[j][i] = sw[i][j];
			}
		}
	}

	return routes;
}

inline Dollars straight_way(City current, City destination, Dollars **sw) {

	return sw[current][destination];
}

size_t index_of(City node, const City nodes[15]) {
	for (size_t n = 0; n < 15; n++) {
		if (nodes[n] == node) { return n; }
	}
}



int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	const City names[] = { Сoфія, Самоков, Дупница, Пернік, Пловдив, Троян, Ямбол, Єлхово,
Кирджалі, Карлово, Варна, Шумен, Плевен, Слівен, Русе };

	Dollars **sw = new Dollars*[15];
	for (int i = 0; i < 15; i++) {
		sw[i] = new Dollars[15];
	}
	Dollars **routes = createMatrix(sw);
	Dollars **half_routes = new Dollars*[15];
	for (int i = 0; i < 15; i++) {
		half_routes[i] = new Dollars[15];
	}
	for (auto start : names) {
		for (auto end : names) {
			if (start == end) continue;
			cout << "From " << start << " To " << end << " Distance " << straight_way(start, end, sw) << " Route: " << endl;
			list<City> route = aStar<City, Dollars, 15>(start, end, names, routes,sw, straight_way);
			for (auto stop : route) {
				cout << stop << " -> ";
			}
			cout << endl;
		
		}
	}

	
	cout << endl;
	system("pause");
}
