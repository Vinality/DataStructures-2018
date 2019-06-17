#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "date.h"

void define(date* d, int month, int day, int year) {
	d->month = month;
	d->day = day;
	d->year = year;
}

int month(date* d) {
	return d->month;
}

int day(date* d) {
	return d->day;
}

int year(date* d) {
	return d->year;
}

void toString(date* d, char* str) {
	sprintf(str,"%d/%d/%d\n",d->month,d->day,d->year);
}
