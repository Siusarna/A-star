#include "queue.h"

void queue::push(const int value, const int prValue) {
	element *temp = new element;
	temp->data = value;
	temp->pr = prValue;
	temp->next = 0;
	if (!this->back) {
		this->back = temp;
		return;
	}

	element *p = this->back, *prev = 0;
	for (; p && compare(temp, p); prev = p, p = p->next);
	if (p == this->back) {
		temp->next = this->back;
		this->back = temp;
		return;
	}
	prev->next = temp;
	if (!p) return;
	temp->next = p;
}

bool queue::compare(element *prev, element *next) {
	return prev->pr < next->pr;
}

bool queue::pop(int &outData, int &outPr) {
	if (!this->back) return false;
	if (!this->back->next) {
		outData = this->back->data;
		outPr = this->back->pr;
		delete this->back;
		this->back = 0;
		return true;
	}
	element *prev, *end;
	prev = end = this->back;
	while (end->next) {
		prev = end;
		end = end->next;
	}
	outData = end->data;
	outPr = end->pr;
	delete end;
	prev->next = 0;
	return true;
}

bool queue::isEmpty() {
	if (this->back == 0) return true;
	return false;
}

void queue::clear() {
	int tempData, tempPr;
	while (!isEmpty()) pop(tempData, tempPr);
}

void queue::print() {
	element *curs = this->back;
	while (curs) {
		cout << curs->data << " ";
		curs = curs->next;
	}
	cout << endl;
}

void editQueue(queue &q, queue &qEdited) {
	int tempData, tempPr;
	int counter = 1;
	while (!q.isEmpty()) {
		q.pop(tempData, tempPr);
		if (counter == 2) {
			qEdited.push(tempData, tempPr + 1);
			counter--;
		}
		else {
			qEdited.push(tempData, tempPr);
			counter++;
		}
	}
}