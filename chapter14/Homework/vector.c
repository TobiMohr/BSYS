#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int main(int argc, char *argv[])
{
	struct vector v = {.data = (int *)malloc(sizeof(int)), .total = 1, .capacity = 1};
	v.data[0] = 8;
	struct vector *pointer = &v;
	vectorAddAtEnd(pointer, 4);
	printf("total values: %d\n", v.total);
	printf("capacity: %d\n", v.capacity);
	
	vectorAddAtEnd(pointer, 9);
	vectorAddAtEnd(pointer, 1);
	
	printf("first value: %d\n", v.data[0]);
	printf("second value: %d\n", v.data[1]);
	printf("third value: %d\n", v.data[2]);
	printf("fourth value: %d\n", v.data[3]);
	printf("total values: %d\n", v.total);
	printf("capacity: %d\n", v.capacity);
	
	int setzung = vectorSet(pointer, 1, 3);
	if (setzung != 0)
	{
		printf("Something went wrong while setting the value");
	}
	printf("new second value: %d --- expected. %d\n", v.data[1], 3);
	
	int del = vectorDelete(pointer, 1);
	if (del != 0)
	{
		printf("Something went wrong while deleting the value");
	}
	printf("new second value after delete: %d --- expected: %d\n", v.data[1], 9);
	printf("new value at the end: %d ------ expected: %d\n", v.data[v.capacity - 1], 0);
	
	printf("total values: %d\n", v.total);
	printf("capacity: %d\n", v.capacity);
	
	int freeit = vectorFree(pointer);
	if (freeit != 0)
	{
		printf("Something went wrong with setting while performing vectorFree()");
	}
	
	return 0;
}