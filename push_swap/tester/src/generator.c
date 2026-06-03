#include "../tester.h"

int	*generate_unique(int size)
{
	int *arr = malloc(sizeof(int) * size);
	int i = 0;

	while (i < size)
	{
		arr[i] = i;
		i++;
	}
	shuffle(arr, size);
	return arr;
}

char	*array_to_args(int *arr, int size)
{
	char *args = malloc(size * 12);
	char tmp[32];
	int i = 0;

	args[0] = '\0';

	while (i < size)
	{
		sprintf(tmp, "%d ", arr[i]);
		strcat(args, tmp);
		i++;
	}
	return args;
}
