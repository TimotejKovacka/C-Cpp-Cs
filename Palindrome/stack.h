#ifndef _Stack_
#define _Stack_
#include <fstream>

class Stack {
char array[21];
std::ofstream &vystup;

public:
	int index;
	Stack(std::ofstream *file);
	bool push(char x);
	char pop();
	char top();
	bool isEmpty();
	void clear();
	void contents();
	int size();
	bool compare(Stack *secondary);
};

#endif