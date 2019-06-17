#ifndef DATE_H_
#define DATE_H_

#define MAX 256

typedef struct {
	int month, day, year;
} date;

void define(date* d, int month, int day, int year);

int month(date* d);

int day(date* d);

int year(date* d);

void toString(date* d, char* str);

#endif
