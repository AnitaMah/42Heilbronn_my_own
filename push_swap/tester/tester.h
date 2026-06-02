#ifndef TESTER_H
# define TESTER_H

# include <stdio.h>

typedef struct s_testset
{
	int				size;
	int				tests;
	int				limit;
}					t_testset;

typedef struct s_stats
{
	int				min;
	int				max;
	long			total;
	int				tests;
	int				failed;
}					t_stats;

/* global access */
extern t_testset	g_tests[];
extern int			g_n_tests;

/* functions */
int					*generate_unique(int size);
char				*array_to_args(int *arr, int size);
void				shuffle(int *arr, int size);

int					run_push_swap(char *args);
int					checker_ok(char *args);
int					count_ops(void);

void				init_stats(void);
void				update_stats(int ops);

void				save_case(int *arr, int size, char *file);

#endif
