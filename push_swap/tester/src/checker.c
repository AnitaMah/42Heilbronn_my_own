#include "tester.h"
#include <string.h>

int	checker_ok(char *args)
{
	char cmd[10000];
	char res[10];

	sprintf(cmd, "./push_swap %s | ./checker_linux %s", args, args);

	FILE *p = popen(cmd, "r");
	if (!p)
		return 0;

	fgets(res, sizeof(res), p);
	pclose(p);

	return (strncmp(res, "OK", 2) == 0);
}
