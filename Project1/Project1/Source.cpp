#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include "a-star.hpp"
#include "greedy.hpp"
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

using Kilometres = double;

Kilometres **createMatrix(Kilometres **&sw) {
	Kilometres **routes = new Kilometres*[15];
	for (int i = 0; i < 15; i++) {
		routes[i] = new Kilometres[15];
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
	
	sw[0][5] = 115; sw[0][6] = 261; sw[0][7] = 272; sw[0][8] = 204; sw[0][10] = 378;
	sw[0][11] = 300; sw[0][12] = 132; sw[0][13] = 245; sw[0][14] = 250; sw[1][3] = 52;
	sw[1][5] = 112; sw[1][6] = 242; sw[1][7] = 253; sw[1][8] = 167; sw[1][9] = 90;
	sw[1][10] = 368; sw[1][11] = 293; sw[1][12] = 147; sw[1][13] = 230; sw[1][14] = 258;
	sw[2][4] = 136; sw[2][5] = 149; sw[2][6] = 280; sw[2][7] = 290; sw[2][8] = 200;
	sw[2][9] = 128; sw[2][10] = 407; sw[2][11] = 331; sw[2][12] = 178; sw[2][13] = 268;
	sw[2][14] = 293; sw[3][4] = 150; sw[3][5] = 140; sw[3][6] = 284; sw[3][7] = 300;
	sw[3][8] = 219; sw[3][9] = 127; sw[3][10] = 403; sw[3][11] = 332; sw[3][12] = 157;
	sw[3][13] = 269; sw[3][14] = 276; sw[4][7] = 154; sw[4][10] = 284; sw[4][11] = 216;
	sw[4][12] = 141; sw[4][13] = 142; sw[4][14] = 214; sw[5][6] = 153; sw[5][7] = 178;
	sw[5][8] = 148; sw[5][10] = 262; sw[5][11] = 184; sw[5][13] = 133; sw[5][14] = 148;
	sw[6][8] = 131; sw[6][9] = 157;  sw[6][10] = 141; sw[6][11] = 94; sw[6][12] = 185;
	sw[6][14] = 158; sw[7][8] = 116;  sw[7][9] = 176; sw[7][10] = 161; sw[7][12] = 218;
	sw[7][14] = 200; sw[8][10] = 271; sw[8][11] = 220; sw[8][12] = 205;
	sw[8][13] = 140; sw[8][14] = 250; sw[9][10] = 278; sw[9][11] = 203; sw[9][14] = 176;
	sw[10][13] = 142; sw[11][12] = 187; sw[11][13] = 81; sw[12][13] = 161;
	
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

inline Kilometres straight_way(City current, City destination, Kilometres **sw) {

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

	Kilometres **sw = new Kilometres*[15];
	for (int i = 0; i < 15; i++) {
		sw[i] = new Kilometres[15];
	}
	Kilometres **routes = createMatrix(sw);
	int distance = 0;
	for (auto start : names) {
		for (auto end : names) {
			if (start == end) continue;
			distance = 0;
			list<City> route = aStar<City, Kilometres, 15>(start, end, names, routes, sw, distance ,straight_way);
			cout << "From " << start << " To " << end << " Distance " << distance << " Route: " << endl;
			for (auto stop : route) {
				cout << stop << " -> ";
			}
			cout << endl;
		}
	}
	cout << endl;
	cout << "Greedy algorithm" << endl;
	cout << endl;
	for (auto start : names) {
		for (auto end : names) {
			if (start == end) continue;
			distance = 0;
			list<City> route = greedy<City, Kilometres, 15>(start, end, names, routes, sw, distance, straight_way);
			cout << "From " << start << " To " << end << " Distance " << distance << " Route: " << endl;
			for (auto stop : route) {
				cout << stop << " -> ";
			}
			cout << endl;

		}
	}
	
	cout << endl;
	system("pause");
}
