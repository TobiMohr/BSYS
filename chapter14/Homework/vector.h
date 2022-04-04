#include <stdio.h>
#include <stdlib.h>

#define UNDEFINE -1
#define SUCCESS 0

struct vector
{
	int  * data;
	int capacity;
	int total;
};

int vectorResize(struct vector *v, int capacity)
{
	int status = UNDEFINE;
	if(v)
	{
		int * data = (int *) realloc(v->data, sizeof(int) * capacity);
		if (data)
		{
			v->data = data;
			v->capacity = capacity;
			status = SUCCESS;
		}
	}
	return status;
}


int vectorAddAtEnd(struct vector *v, int value)
{
	int status = UNDEFINE;
	if (v)
	{
		if (v->capacity == v->total)
		{
			status = vectorResize(v, v->capacity * 2);
			if (status != UNDEFINE)
			{
				v->data[v->total++] =value;
			}
		}
		else
		{
			v->data[v->total++] = value;
			status = SUCCESS;
		}
	}
	return status;
}

int vectorSet(struct vector *v, int index, int value)
{
	int status = UNDEFINE;
	if(v)
	{
		if ((index >= 0) && (index < v->total))
		{
			v->data[index] = value;
			status = SUCCESS;
		}
	}
	return status;
}

int vectorDelete(struct vector *v, int index)
{
	int status = UNDEFINE;
	int i = 0;
	if(v)
	{
		if((index < 0) || (index >= v->total))
			return status;
		
		v->data[index] = 0;
		
		for (i = index; (i < v->total - 1); i++)
		{
			v->data[i] = v->data[i + 1];
			v->data[i + 1] = 0;
		}
		
		v->total--;
		
		if ((v->total > 0) && ((v->total) == (v->capacity / 4)))
		{
			vectorResize(v, v->capacity / 2);
		}
		status = SUCCESS;
	}
	return status;
}

int vectorFree(struct vector *v)
{
	int status = UNDEFINE;
	if(v)
	{
		free(v->data);
		v->total = 0;
		v->capacity = 0;
		status = SUCCESS;
	}
	return status;
}