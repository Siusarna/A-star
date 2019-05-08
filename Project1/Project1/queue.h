#include <iostream>
using namespace std;


struct element {
	int data;
	unsigned int pr;
	element *next;
};

struct queue {
	element *back = 0;
	void push(const int value, const int prValue);
	bool pop(int &outData, int &outPr);
	bool compare(element *prev, element *next);
	bool isEmpty();
	void print();
	void clear();

};