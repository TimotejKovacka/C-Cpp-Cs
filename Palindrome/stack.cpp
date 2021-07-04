#include <iostream>
#include <fstream>
#include "stack.h"
using namespace std;

//Konstrukcna funkcia pre stack
Stack::Stack(std::ofstream *file):vystup(*file) {
	index = -1;
}

//Tato funkcia prida element do stacku
bool Stack::push(char x) {
	if (index >= 20) {
		cout << "Stack overflow";
		vystup << "Stack overflow\n";
		return false;
	}
	array[++index] = x;
	vystup << "Character " << x << " was added\n";
	return true;
}

//Tato funkcia vrati vrchny element a vyprazdni ho zo stacku
char Stack::pop() {
	if (index < 0) {
		cout << "Stack underflow";
		vystup << "Stack underflow\n";
	}
	char x = array[index--];
	vystup << "Character popped from stack " << x << "\n";
	
	return x;
}

//Tato funckia zisti aky element navrchu
char Stack::top() {
	if (index < 0) {
		cout << "Stack is empty";
		vystup << "Stack is empty\n";
		return 0;
	}
	char x = array[index];
	return x;
}

//Tato funkcia skontroluje ci je stack prazdny
bool Stack::isEmpty() {
	if (index < 0) {
		vystup << "Stack is empty\n";
		return true;
	}
	vystup << "Stack is not empty\n";
	return false;
}

//Tato funckia vyprazdny stack
void Stack::clear() {
	index = -1;
	vystup << "Stack was cleared\n";
}

//Tato funkcia vypise obsah stacku a zachova ho
void Stack::contents() {
	vystup << "Stack contains: ";
	for (unsigned int i = 0; i <= index; i++) {
		cout << array[i];
		vystup << array[i];
	}
	cout << "\n";
	vystup << "\n";
}

//Tato funkcia vypise kolko elementov obsahuje stack
int Stack::size() {
	vystup << "Size of stack is: " << index+1 << "\n";
	return index+1;
}

//Tato funkcia skontroluje 2 stacky voci sebe a porovna ich obsah a ci tvoria palindrom a zachova stacky
bool Stack::compare(Stack *secondary) {
	
	if (size() != secondary->size()){
		cout << "String is not a palindrome\n";
		vystup << "String is not a palindrome\n";
		
		return false;
	}
	for (unsigned int i = 0; i <= index; i++) {
		if (array[i] != secondary->array[i]) {
			cout << "String is not a palindrome\n";
			vystup << "String is not a palindrome\n";
			return false;
		}
	}
	cout << "String is a palindrome\n";
	vystup << "String is a palindrome\n";
	return true;
}
