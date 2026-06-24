/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 16:17:37 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/24 16:55:00 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>

/* ========================================================================== */
/** @defgroup config Strategy Flags
 *  @brief Runtime configuration for sorting behavior.
 *  @{
 */
# define STRATEGY_SIMPLE 0
# define STRATEGY_MEDIUM 1
# define STRATEGY_COMPLEX 2
# define STRATEGY_ADAPTIVE 3
/** @} */
/* ========================================================================== */

/* ========================================================================== */
/** @defgroup opcodes Operation Codes
 *  @brief Internal operation identifiers for dispatcher system.
 *  @{
 */
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
/** @} */
/* ========================================================================== */

/* ========================================================================== */
/** @defgroup structures Core Data Structures
 *  @brief Stack system and runtime containers.
 *  @{
 */

typedef struct s_node
{
	int				value;
	int				index;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef struct s_stack
{
	t_node		*top;
	t_node		*bottom;
	int			size;
	int			chunk_size;
	char		name;
}					t_stack;

typedef struct s_input
{
	int			*arr;
	int			size;
}					t_input;

typedef struct s_flags
{
	int			strategy;
	int			bench;
}					t_flags;

typedef struct s_context
{
	t_stack		*a;
	t_stack		*b;
	t_input		*in;
	t_flags		*flags;
}					t_context;

/** @} */
/* ========================================================================== */

/* ========================================================================== */
/** @defgroup operations Stack Operations
 *  @brief Primitive stack manipulation functions.
 *  @{
 */

void	sa(t_stack *a);
void	sb(t_stack *b);
void	ss(t_stack *a, t_stack *b);

void	pa(t_stack *a, t_stack *b);
void	pb(t_stack *a, t_stack *b);

void	ra(t_stack *a);
void	rb(t_stack *b);
void	rr(t_stack *a, t_stack *b);

void	rra(t_stack *a);
void	rrb(t_stack *b);
void	rrr(t_stack *a, t_stack *b);

/** @} */
/* ========================================================================== */

/* ========================================================================== */
/** @defgroup sorting Sorting Engine
 *  @brief All sorting strategies and helpers.
 *  @{
 */

/**
 * @brief Main sorting dispatcher.
 *
 * Selects optimal algorithm based on:
 * - input disorder level
 * - runtime flags (strategy/bench)
 *
 * Uses flags to influence algorithm choice.
 */
void	sort_stack(t_stack *a, t_stack *b, t_flags *flags, double disorder);

void	radix_sort(t_stack *a, t_stack *b);
void	chunk_sort(t_stack *a, t_stack *b);
void	selection_sort_adaptation(t_stack *a, t_stack *b);

void	sort_two(t_stack *a);
void	sort_three(t_stack *a);
void	sort_four_five(t_stack *a, t_stack *b, int size);
void	sort_five(t_stack *a, t_stack *b);

void	quicksort(int *arr, int left, int right);
void	normalize_index(t_stack *a);

void	bring_to_top(t_stack *stack, t_node *target);
void	restore_to_a(t_stack *a, t_stack *b);

t_node	*find_max(t_stack *b);
int		find_position(t_stack *stack, int index_limit);

/** @} */
/* ========================================================================== */

/* ========================================================================== */
/** @defgroup parsing Initialization & Parsing
 *  @brief Argument parsing and environment setup.
 *  @{
 */

int		init_environment(int argc, char **argv, t_context *ctx);
int		init_and_fill_stack(t_stack *a, int argc, char **argv, t_input *in);

void	init_stack(t_stack *stack, char name);

int		stack_from_array(t_stack *a, int *arr, int size);

int		*parse_args(int argc, char **argv, int *size);
int		handle_args(int argc, char **argv, int *nums, int mode);
int		fill_all_nums(int argc, char **argv, int *nums);
int		fill_single_split(char **split, int *nums, int *k);

int		count_total_words(int argc, char **argv);
int		count_words_in_split(char **split);
int		count_args(char **args);

int		is_valid_number(char *s);
int		ft_atoi_ps(const char *str, int *error);
int		check_duplicates(int *array, int size);

/** @} */
/* ========================================================================== */

/* ========================================================================== */
/** @defgroup utils Utilities
 *  @brief Helper and runtime functions.
 *  @{
 */

int		is_sorted(t_stack *a);
double	compute_disorder(int *arr, int size);
int		stack_to_array(t_stack *a);

int		op_counter(int mode);
void	execute_rotation(t_stack *stack, int ops);

void	sort_stack(t_stack *a, t_stack *b, t_flags *flags, double disorder);

void	run_sorting(t_stack *a, t_stack *b, t_flags *f, t_input *in);

void	cleanup(t_stack *a, t_stack *b);
void	free_stack(t_stack *a);
void	free_split(char **arr);
void	free_args_if_split(int argc, char **args);

/** @} */
/* ========================================================================== */

#endif