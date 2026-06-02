#include "tester.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ================= GLOBAL TEST CONFIG ================= */

t_testset	g_tests[] = {{3, 100, 3}, {5, 100, 12}, {10, 100, 25}, {50, 100,
		350}, {100, 100, 700}, {500, 20, 5500}};

int			g_n_tests = sizeof(g_tests) / sizeof(g_tests[0]);

/* ================= STATS ================= */

typedef struct s_stats
{
	int		min;
	int		max;
	long	total;
	int		tests;
	int		failed;
}			t_stats;

t_stats		g_stats;

void	init_stats(void)
{
	g_stats.min = 1000000;
	g_stats.max = 0;
	g_stats.total = 0;
	g_stats.tests = 0;
	g_stats.failed = 0;
}

void	update_stats(int ops)
{
	if (ops < g_stats.min)
		g_stats.min = ops;
	if (ops > g_stats.max)
		g_stats.max = ops;
	g_stats.total += ops;
	g_stats.tests++;
}

/* ================= OPS COUNT ================= */

int	count_ops(void)
{
	FILE	*f;
	char	line[100];
	int		count;

	f = fopen("result.txt", "r");
	count = 0;
	if (!f)
		return (0);
	while (fgets(line, sizeof(line), f))
		count++;
	fclose(f);
	return (count);
}

/* ================= MAIN ================= */

int	main(void)
{
	srand(time(NULL));
	init_stats();

	for (int i = 0; i < g_n_tests; i++)
	{
		printf("\n===== SIZE %d =====\n", g_tests[i].size);

		for (int t = 0; t < g_tests[i].tests; t++)
		{
			int *arr = generate_unique(g_tests[i].size);
			char *args = array_to_args(arr, g_tests[i].size);

			run_push_swap(args);

			int ops = count_ops();
			int ok = checker_ok(args);

			if (!ok)
			{
				printf("❌ KO\n");
				save_case(arr, g_tests[i].size, "test_cases/worst_case.txt");
				g_stats.failed++;
				break ;
			}

			if (ops > g_tests[i].limit)
				printf("⚠️ Too many ops: %d (limit %d)\n", ops,
					g_tests[i].limit);

			update_stats(ops);

			free(arr);
			free(args);
		}
	}

	printf("\n===== FINAL REPORT =====\n");
	printf("Tests: %d\n", g_stats.tests);
	printf("Failed: %d\n", g_stats.failed);
	printf("Min ops: %d\n", g_stats.min);
	printf("Max ops: %d\n", g_stats.max);
	printf("Avg ops: %ld\n", g_stats.total / g_stats.tests);

	return (0);
}
