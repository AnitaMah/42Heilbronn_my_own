/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 16:17:37 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/18 15:02:23 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# define STRATEGY_SIMPLE 0
# define STRATEGY_MEDIUM 1
# define STRATEGY_COMPLEX 2
# define STRATEGY_ADAPTIVE 3

# define OP_SA 0
# define OP_SB 1
# define OP_SS 2
# define OP_PA 3
# define OP_PB 4
# define OP_RA 5
# define OP_RB 6
# define OP_RR 7
# define OP_RRA 8
# define OP_RRB 9
# define OP_RRR 10
# define OP_TOTAL 11

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>

/* --- FLAGS STRUCTURE --- */

typedef struct s_flags
{
	int				strategy;
	int				bench;
	int				count_only;
}					t_flags;

/* --- STACK STRUCTURES --- */

typedef struct s_node
{
	int				value;
	int				index;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef struct s_stack
{
	t_node			*top;
	t_node			*bottom;
	int				size;
	int				chunk_size;
	char			name;
}					t_stack;

typedef struct s_input
{
	int				*arr;
	int				size;
}					t_input;

typedef struct s_context
{
	t_stack			*a;
	t_stack			*b;
	t_input			*in;
	t_flags			*flags;
}					t_context;

/* --- STACK OPERATIONS --- */

/* Swap top two elements of stack A */
void				sa(t_stack *a, t_flags *apply);

/* Swap top two elements of stack B */
void				sb(t_stack *b, t_flags *apply);

/* Swap top two elements of both stacks */
void				ss(t_stack *a, t_stack *b, t_flags *apply);

/* Push top element from B to A */
void				pa(t_stack *a, t_stack *b, t_flags *apply);

/* Push top element from A to B */
void				pb(t_stack *a, t_stack *b, t_flags *apply);

/* Rotate stack A upwards */
void				ra(t_stack *a, t_flags *apply);

/* Rotate stack B upwards */
void				rb(t_stack *b, t_flags *apply);

/* Rotate both stacks upwards */
void				rr(t_stack *a, t_stack *b, t_flags *apply);

/* Reverse rotate stack A */
void				rra(t_stack *a, t_flags *apply);

/* Reverse rotate stack B */
void				rrb(t_stack *b, t_flags *apply);

/* Reverse rotate both stacks */
void				rrr(t_stack *a, t_stack *b, t_flags *apply);

/* --- SORTING ALGORITHMS --- */

/* Quick sort for array normalization */
void				quicksort(int *arr, int left, int right);

/* Convert stack values into normalized indexes */
void				normalize_index(t_stack *a);

/* Chunk-based sorting algorithm */
void				chunk_sort(t_stack *a, t_stack *b, t_flags *apply);

/* Move target node to top of stack efficiently */
void				bring_to_top(t_stack *stack, t_node *target,
						t_flags *apply);

/* Restore all elements from B back to A */
void				restore_to_a(t_stack *a, t_stack *b, t_flags *apply);

/* Find node with maximum index in stack B */
t_node				*find_max(t_stack *b);

/* Radix sort (bitwise sorting) */
void				radix_sort(t_stack *a, t_stack *b, t_flags *apply);

/* Simple selection sort adaptation */
void				selection_sort_adaptation(t_stack *a, t_stack *b,
						t_flags *apply);

/* Sort 5 elements */
void				sort_five(t_stack *a, t_stack *b, t_flags *apply);

/* Sort 4–5 elements */
void				sort_four_five(t_stack *a, t_stack *b, int size,
						t_flags *apply);

/* Sort 3 elements */
void				sort_three(t_stack *a, t_flags *apply);

/* Sort 2 elements */
void				sort_two(t_stack *a, t_flags *apply);

/* Convert stack to array */
int					stack_to_array(t_stack *a);

/* Compute disorder level (0 sorted -> 1 random) */
double				compute_disorder(int *arr, int size);

/* --- CORE FUNCTIONS --- */

/* Initialize stack structure */
void				init_stack(t_stack *stack, char name);

/* Check if stack A is sorted */
int					is_sorted(t_stack *a);

/* Main sorting dispatcher */
void				sort_stack(t_stack *a, t_stack *b, t_flags *flags,
						double disorder);

/* Free all nodes in a stack */
void				free_stack(t_stack *a);

/* Execute specific rotation/operation */
void				execute_rotation(t_stack *stack, int ops, t_flags *apply);

/* --- FLAGS --- */
void				parse_flags(int argc, char **argv, t_flags *flags);
int					is_flag(char *s, char *flag);

/* --- BENCH --- */
int					op_counter(int mode);
void				print_bench(t_flags *flags, double disorder);

/* --- PARSING FUNCTIONS --- */

/* Count the number of strings in a split array */
int					count_words_in_split(char **split);

/* Populate integer array from split strings */
int					fill_single_split(char **split, int *nums, int *k);

/* Parse argv into integer array */
int					*parse_args(int argc, char **argv, int *size);
int					handle_args(int argc, char **argv, int *nums, int mode);

/* Build stack from array */
int					stack_from_array(t_stack *a, int *arr, int size);

/* Validate if a string is a valid number */
int					is_valid_number(char *s);

/* Count the number of arguments */
int					count_args(char **args);
int					count_total_words(int argc, char **argv);
int					fill_all_nums(int argc, char **argv, int *nums);

/* Free arguments if split was used */
void				free_args_if_split(int argc, char **args);

/* Safe atoi with overflow/error check */
int					ft_atoi_ps(const char *str, int *error);

/* Check array for duplicate integers */
int					check_duplicates(int *array, int size);
void				free_split(char **arr);
int					find_position(t_stack *stack, int index_limit);

int					init_environment(int argc, char **argv, t_context *ctx);
void				run_sorting(t_stack *a, t_stack *b, t_flags *f,
						t_input *in);
int					init_and_fill_stack(t_stack *a, int argc, char **argv,
						t_input *in);
void				cleanup(t_stack *a, t_stack *b);

void				print_count_only(t_flags *apply);

#endif
