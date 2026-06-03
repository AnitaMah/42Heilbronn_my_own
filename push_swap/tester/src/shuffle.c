#include "../tester.h"

static void	swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void	shuffle(int *arr, int size)
{
	int i = size - 1;

	while (i > 0)
	{
		int j = rand() % (i + 1);
		swap(&arr[i], &arr[j]);
		i--;
	}
}
