#include "tester.h"
#include <stdio.h>
#include <stdlib.h>

/*
** Count operations (lines of push_swap output)
*/
static int count_ops(const char *str)
{
	int i = 0;
	int ops = 0;

	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			ops++;
		i++;
	}
	return (ops);
}

/*
** Run push_swap and capture output safely
*/
int run_push_swap(char *args)
{
	char	cmd[4096];
	char	buffer[100000];
	FILE	*fp;
	int		ops;
	size_t	read_bytes;

	/*
	** IMPORTANT:
	** we redirect stdout of push_swap into tester
	*/
	snprintf(cmd, sizeof(cmd), "../push_swap %s", args);

	fp = popen(cmd, "r");
	if (!fp)
		return (-1);

	read_bytes = fread(buffer, 1, sizeof(buffer) - 1, fp);
	buffer[read_bytes] = '\0';

	pclose(fp);

	ops = count_ops(buffer);

	return ops;
}