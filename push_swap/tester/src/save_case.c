#include "../tester.h"
#include <stdio.h>

void save_case(int *arr, int size, const char *file)
{
	FILE *f;
	int i = 0;

	f = fopen(file, "w");
	if (!f)
		return;

	while (i < size)
	{
		fprintf(f, "%d ", arr[i]);
		i++;
	}
	fprintf(f, "\n");
	fclose(f);
}