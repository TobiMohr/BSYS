#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int *data = (int *) malloc(25 * sizeof(int));
	data[10] = 8;
	free(&data[10]);
	return 0;
}