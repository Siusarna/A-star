#include <iostream>
#include <fstream>
#include <list>
#include "a-star.hpp"

/*
# Airport Example:
This exmaple hopes to determine the cheapest route from one airport to another
using the flight time as a heuristic.
Finding flight routes are a good case for adjacency matrix digraphs because they
tend to be dense (it's possible to fly from nearly any airport to any other
airport), making them memory efficient.
A-star finds the cheapest route by exploring all of the neighbour airports to
find the airport with the lowest flight time to the destination and lowset Cost
from the start until it finds the optimal path.
 */

enum Airport { LAX, MIA, ATL, DEN, JFK };

// Define stream insertion for pretty printing

using Dollars = double;

// Flight time in minutes between airports to use as heuristic for A*
inline Dollars flight_time(Airport current, Airport destination) {
	Dollars times[5][5] = {
		//LAX   MIA   ATL   DEN   JFK
		{   0, 4 * 60, 3 * 60, 1 * 60, 5 * 60}, // LAX
		{4 * 60,    0, 1 * 60, 4 * 60, 3 * 60}, // MIA
		{3 * 60, 2 * 60,    0, 2 * 60, 4 * 60}, // ATL
		{1 * 60, 4 * 60, 2 * 60,    0, 4 * 60}, // DEN
		{5 * 60, 3 * 60, 3 * 60, 4 * 60,    0}  // JFK
	};

	return times[current][destination];
}

int main() {

	// Define vertex names which correspond to matrix row and column    // labels
	const Airport names[] = { LAX, MIA, ATL, DEN, JFK };

	// Define adjacency matrix where flights from each row airport to each
	// column airport correspond to an edge with the associated cost
	const Dollars routes[][5] = {
		//LAX MIA  ATL  DEN  JFK
		{  0, 500, 200, 136, 299}, // LAX
		{438,   0, 114, 330, 247}, // MIA
		{204, 104,   0, 199, 205}, // ATL
		{116, 300, 164,   0, 247}, // DEN
		{275, 230, 198, 212,   0}  // JFK
	};

	std::list<Airport> route = aStar<Airport, Dollars>(LAX, MIA, names, routes, flight_time);

	std::cout << "Cheapest route, expect LAX -> ATL -> MIA,\nfound ";
	for (auto stop : route) {
		std::cout << " -> " << stop;
	}
}

double **createMatrix(double **&sw) {
	double **arr = new double*[15];
	for (int i = 0; i < 15; i++) {
		arr[i] = new double[15];
		arr[i][i] = 0;
		for (int j = 0; i < 15; j++) {
			arr[i][j] = 0;
			sw[i][j] = 0;
		}
	}
	arr[0][1] = 57.6; arr[0][2] = 67.1;  arr[0][3] = 35.2;  arr[0][4] = 143;  arr[0][9] = 139;
	arr[1][2] = 40.3; arr[1][4] = 145;  arr[2][3] = 49.7;  arr[4][5] = 125;
	arr[4][6] = 168;  arr[4][8] = 95;  arr[4][9] = 60.5; arr[5][9] = 69.6;
	arr[5][12] = 70.1; arr[6][7] = 38.2; arr[6][13] = 28.9;  arr[7][11] = 167;
	arr[7][13] = 68.6;  arr[8][9] = 190;  arr[9][12] = 140; arr[9][13] = 140;
	arr[10][11] = 88.9;  arr[10][12] = 300; arr[10][14] = 215;  arr[11][14] = 111;
	arr[12][14] = 151;  arr[13][14] = 211;
	for (int i = 0; i < 15; i++) {
		for (int j = i; j < 15; j++) {
			if (arr[i][j] != 0) {
				arr[j][i] = arr[i][j];
			}
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
				sw[i][j] = arr[i][j];
				sw[j][i] = arr[i][j];
			}
			if (sw[i][j] != 0) {
				sw[j][i] = sw[i][j];
			}
		}
	}


	return arr;
}
