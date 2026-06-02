#include "tester.h"

int	check_leaks(char *args)
{
	char cmd[10000];

	sprintf(cmd, "valgrind --leak-check=full ./push_swap %s > /dev/null 2>&1",
		args);

	return (system(cmd));
}
