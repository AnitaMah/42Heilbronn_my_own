#include "../tester.h"
#include <stdio.h>
#include <stdlib.h>

/*
** global stats
*/
t_stats g_stats;

/*
** test config
*/
t_testset g_tests[] =
{
	{3, 100, 3},
	{5, 100, 12},
	{10, 100, 25},
	{50, 100, 350},
	{100, 100, 700},
	{500, 20, 5500}
};

int main(void)
{
	int i;
	int t;
	int ops;
	int ok;

	init_stats(&g_stats);

	i = 0;
	while (i < (int)(sizeof(g_tests) / sizeof(g_tests[0])))
	{
		printf("\n===== SIZE %d =====\n", g_tests[i].size);

		t = 0;
		while (t < g_tests[i].tests)
		{
			int *arr = generate_unique(g_tests[i].size);
			char *args = array_to_args(arr, g_tests[i].size);

			run_push_swap(args);

			ok = checker_ok(args);
			ops = ok; // ⚠️ заміни якщо у тебе є реальний ops

			if (ops > g_tests[i].limit)
			{
				printf("❌ FAIL: %d ops (limit %d)\n",
					ops, g_tests[i].limit);
				g_stats.failed++;
			}
			else
			{
				printf("✔ OK: %d ops\n", ops);
			}

			update_stats(&g_stats, ops);

			// optional worst case save
			if (ops > g_tests[i].limit)
				save_case(arr, g_tests[i].size, "test_cases/worst_case.txt");

			free(arr);
			free(args);

			t++;
		}
		i++;
	}

	printf("\n===== RESULTS =====\n");
	printf("Min ops: %d\n", g_stats.min);
	printf("Max ops: %d\n", g_stats.max);
	printf("Avg ops: %d\n",
		g_stats.total / (g_stats.tests ? g_stats.tests : 1));
	printf("Failed: %d\n", g_stats.failed);

	return 0;
}