/*
	Timotej Kovacka, 2478424k, SP Exercise 1a
	This is my own work except numPlaces() function to which you can find link in a comment above it
*/

#include "date.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


struct date {
	int day;
	int month;
	int year;
};

/* Function taken from https://stackoverflow.com/questions/1068849/how-do-i-determine-the-number-of-digits-of-an-integer-in-c */
int numPlaces(int n) {
	if (n < 0) n = (n == INT_MIN) ? INT_MAX : -n;
	if (n < 10) return 1;
	if (n < 100) return 2;
	if (n < 1000) return 3;
	if (n < 10000) return 4;
	if (n < 100000) return 5;
	if (n < 1000000) return 6;
	if (n < 10000000) return 7;
	if (n < 100000000) return 8;
	if (n < 1000000000) return 9;
	/*      2147483647 is 2^31-1 - add more ifs as needed
	   and adjust this final return as well. */
	return 10;
}

Date* date_create(char* datestr) {
	int day, month, year;
	char x[2];
	if (sscanf(datestr, "%2d%c%2d%c%4d", &day, &x[0], &month, &x[1], &year) == EOF) return NULL;
	if ((x[0] != x[1] ) && x[0] != '/') return NULL;
	if (numPlaces(day) > 2 || numPlaces(month) > 2 || numPlaces(year) != 4) return NULL;
	Date* temp = (Date*)malloc(sizeof(Date));
	if (!temp) return NULL;
	temp->day = day;
	temp->month = month;
	temp->year = year;
	return temp;
};

Date* date_duplicate(Date* d) {
	Date* duplicate = (Date*)malloc(sizeof(Date));
	if (!duplicate) return NULL;
	duplicate->day = d->day;
	duplicate->month = d->month;
	duplicate->year = d->year;
	return duplicate;
};

int date_compare(Date* date1, Date* date2) {
	if (date1->year == date2->year) {
		if (date1->month == date2->month) {
			if (date1->day == date2->day) {
				return 0;
			}
			else if (date1->day < date2->day) return -1;
			else return 1;
		}
		else if (date1->month < date2->month) return -1;
		else return 1;
	}
	else if (date1->year < date2->year) return -1;
	else return 1;
};

void date_destroy(Date* d) {
	free(d);
};