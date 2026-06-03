#ifndef TESTER_H
# define TESTER_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>

# define PUSH_SWAP "../push_swap/push_swap"
# define CHECKER   "../checker_linux"

/*
** =========================
**        STRUCTS
** =========================
*/

typedef struct s_stats
{
	int	min;
	int	max;
	int	total;
	int	tests;
	int	failed;
}	t_stats;

typedef struct s_testset
{
	int	size;
	int	tests;
	int	limit;
}	t_testset;

/*
** =========================
**        CORE
** =========================
*/

void	init_stats(t_stats *stats);
void	update_stats(t_stats *stats, int ops);

/*
** =========================
**        GENERATOR
** =========================
*/

int		*generate_unique(int size);
char	*array_to_args(int *arr, int size);
void	save_case(int *arr, int size, const char *path);
void	shuffle(int *arr, int size);

/*
** =========================
**        RUNNER
** =========================
*/

int		run_push_swap(char *args);
int		checker_ok(char *args);

#endif