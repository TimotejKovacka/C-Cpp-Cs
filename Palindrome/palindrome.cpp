#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"
using namespace std;

int main() {

	char option;
	bool Aoption = false;
	Stack *a = NULL, *b = NULL;
	ofstream vystup("log.txt", std::ofstream::out);
	cout << "To interact with program use the following menu:" << endl 
		<< "<a> Creates 2 stacks to hold input data" << endl
		<< "<b> Clear data from stacks" << endl
		<< "<c> Select this option to store your input from following line to stacks" << endl
		<< "<d> Print contents of 1st stack to screen" << endl
		<< "<e> Print contents of 2nd stack to screen" << endl
		<< "<f> Compare data between the 2 stacks to see if your input is a palindrome" << endl
		<< "<x> Select this to terminate programm" << endl
		<< "To use menu, type its name like so: a" << endl;
	do {
		cin >> option;
		tolower(option);
		if (option == 'a' && !Aoption) {
			Aoption = true;
			a = new Stack(&vystup);
			b = new Stack(&vystup);
		}
		else if (!Aoption) {
			continue;
		}
		if (option == 'b') {
			a->clear();
			b->clear();
		} else if (option == 'c') {
			string input;
			cin >> input;
			char* input_array = new char [input.length()+1];
			strcpy_s(input_array, input.length()+1, input.c_str());
			for (int i = 0; i < input.length(); i++) {
				a->push(input_array[i]);
			}
			for (int i = input.length()-1; i >= 0 ; i--) {
				b->push(input_array[i]);
			}
		} else if (option == 'd') {
			a->contents();
		} else if (option == 'e') {
			b->contents();
		} else if (option == 'f') {
			a->compare(b);
		}
	} while (option!='x');
	vystup.close();
	delete a, b;
	return 0;
}