#include "tester.h"

int	run_push_swap(char *args)
{
	char	cmd[10000];

	sprintf(cmd, "./push_swap %s > result.txt", args);
	return (system(cmd));
}
