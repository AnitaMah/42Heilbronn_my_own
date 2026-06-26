/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 16:17:37 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/26 13:47:59 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# define STRATEGY_NONE -1
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

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>

/* ========================================================================== */
/* STRUCTURE DEFINITIONS                           							  */
/* ========================================================================== */

typedef struct s_flags
{
	int				strategy;
	int				bench;
}					t_flags;

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

/* ========================================================================== */
/* STACK OPERATIONS                               							  */
/* ========================================================================== */

/**
 * @brief Swaps the top two elements of stack A.
 * @param a Pointer to the stack structure A.
 */
void				sa(t_stack *a);

/**
 * @brief Swaps the top two elements of stack B.
 * @param b Pointer to the stack structure B.
 */
void				sb(t_stack *b);

/**
 * @brief Swaps the top two elements of both stacks.
 * @param a Pointer to stack A, @param b Pointer to stack B.
 */
void				ss(t_stack *a, t_stack *b);

/**
 * @brief Pushes the top element from stack B to A.
 * @param a Pointer to stack A, @param b Pointer to stack B.
 */
void				pa(t_stack *a, t_stack *b);

/**
 * @brief Pushes the top element from stack A to B.
 * @param a Pointer to stack A, @param b Pointer to stack B.
 */
void				pb(t_stack *a, t_stack *b);

/**
 * @brief Rotates stack A upwards.
 * @param a Pointer to the stack structure A.
 */
void				ra(t_stack *a);

/**
 * @brief Rotates stack B upwards.
 * @param b Pointer to the stack structure B.
 */
void				rb(t_stack *b);

/**
 * @brief Rotates both stacks upwards.
 * @param a Pointer to stack A, @param b Pointer to stack B.
 */
void				rr(t_stack *a, t_stack *b);

/**
 * @brief Reverse rotates stack A.
 * @param a Pointer to the stack structure A.
 */
void				rra(t_stack *a);
/**
 * @brief Reverse rotates stack B.
 * @param b Pointer to the stack structure B.
 */
void				rrb(t_stack *b);

/**
 * @brief Reverse rotates both stacks.
 * @param a Pointer to stack A, @param b Pointer to stack B.
 */
void				rrr(t_stack *a, t_stack *b);

/* ========================================================================== */
/* SORTING ALGORITHMS                             							  */
/* ========================================================================== */

/**
 * @brief Performs quicksort on an integer array.
 * @param arr Array, @param left start, @param right end.
 */
void				quicksort(int *arr, int left, int right);

/**
 * @brief Converts stack values into normalized indexes.
 * @param a Pointer to the stack structure A.
 */
void				normalize_index(t_stack *a);

/**
 * @brief Executes chunk-based sorting algorithm.
 * @param a Pointer to stack A, @param b Pointer to stack B.
 */
void				chunk_sort(t_stack *a, t_stack *b);

/**
 * @brief Moves target node to top of stack efficiently.
 * @param stack The target stack, @param target Node to move.
 */
void				bring_to_top(t_stack *stack, t_node *target);

/**
 * @brief Restores all elements from B back to A.
 * @param a Pointer to stack A, @param b Pointer to stack B.
 */
void				restore_to_a(t_stack *a, t_stack *b);

/**
 * @brief Finds node with maximum index in stack B.
 * @param b Pointer to the stack structure B.
 */
t_node				*find_max(t_stack *b);

/**
 * @brief Executes bitwise radix sort algorithm.
 * @param a Pointer to stack A, @param b Pointer to stack B.
 */
void				radix_sort(t_stack *a, t_stack *b);

/**
 * @brief Adaptation of simple selection sort.
 * @param a Pointer to stack A, @param b Pointer to stack B.
 */
void				selection_sort_adaptation(t_stack *a, t_stack *b);

/**
 * @brief Sorts a stack of five elements.
 * @param a Pointer to stack A, @param b Pointer to stack B.
 */
void				sort_five(t_stack *a, t_stack *b);

/**
 * @brief Handles sorting for four or five elements.
 * @param a Pointer to stack A, @param b Pointer to stack B, @param size.
 */
void				sort_four_five(t_stack *a, t_stack *b, int size);

/**
 * @brief Sorts a stack of three elements.
 * @param a Pointer to the stack structure A.
 */
void				sort_three(t_stack *a);

/**
 * @brief Sorts a stack of two elements.
 * @param a Pointer to the stack structure A.
 */
void				sort_two(t_stack *a);

/**
 * @brief Converts stack to an integer array.
 * @param a Pointer to the stack structure A.
 */
int					stack_to_array(t_stack *a);

/**
 * @brief Computes disorder level of an array.
 * @param arr Input array, @param size Size of array.
 */
double				compute_disorder(int *arr, int size);

/* ========================================================================== */
/* CORE FUNCTIONS                              								  */
/* ========================================================================== */

/**
 * @brief Initializes the stack structure.
 * @param stack Stack to init, @param name Label ('a' or 'b').
 */
void				init_stack(t_stack *stack, char name);

/**
 * @brief Checks if stack A is sorted.
 * @param a Pointer to the stack structure A.
 */
int					is_sorted(t_stack *a);

/**
 * @brief Dispatches the appropriate sorting algorithm.
 * @param a, @param b, @param flags, @param disorder metric.
 */
void				sort_stack(t_stack *a, t_stack *b, t_flags *flags,
						double disorder);

/**
 * @brief Frees all nodes in a stack.
 * @param a Pointer to the stack structure A.
 */
void				free_stack(t_stack *a);

/**
 * @brief Executes a specific rotation/operation.
 * @param stack The stack, @param ops The operation code.
 */
void				execute_rotation(t_stack *stack, int ops);

/* ========================================================================== */
/* PARSING                                   								  */
/* ========================================================================== */

/**
 * @brief Parses command line arguments into flags.
 * @param argc, @param argv, @param flags structure.
 */
void				parse_flags(int argc, char **argv, t_flags *flags);

/**
 * @brief Checks if a string matches a flag.
 * @param s Input string, @param flag The flag char.
 */
int					is_flag(char *s, char *flag);

/**
 * @brief Counts and returns operation count.
 * @param mode Operation mode or reset.
 */
int					op_counter(int mode);

/**
 * @brief Prints performance benchmark data.
 * @param flags, @param disorder metric.
 */
void				print_bench(t_flags *flags, double disorder);

/**
 * @brief Counts number of strings in a split array.
 * @param split The split string array.
 */
int					count_words_in_split(char **split);

/**
 * @brief Populates array from split strings.
 * @param split, @param nums, @param k index tracker.
 */
int					fill_single_split(char **split, int *nums, int *k);

/**
 * @brief Parses arguments into an integer array.
 * @param argc, @param argv, @param size pointer.
 */
int					*parse_args(int argc, char **argv, int *size);

/**
 * @brief Handles argument processing based on mode.
 * @param argc, @param argv, @param nums, @param mode.
 */
int					handle_args(int argc, char **argv, int *nums, int mode);

/**
 * @brief Builds a stack from an integer array.
 * @param a The stack, @param arr, @param size.
 */
int					stack_from_array(t_stack *a, int *arr, int size);

/**
 * @brief Validates if string is a valid number.
 * @param s The string to validate.
 */
int					is_valid_number(char *s);

/**
 * @brief Counts total arguments/words.
 * @param argc, @param argv.
 */
int					count_args(char **args);
int					count_total_words(int argc, char **argv);
int					fill_all_nums(int argc, char **argv, int *nums);

/**
 * @brief Frees arguments if they were split.
 * @param argc, @param args.
 */
void				free_args_if_split(int argc, char **args);

/**
 * @brief Secure atoi with error handling.
 * @param str, @param error pointer.
 */
int					ft_atoi_ps(const char *str, int *error);

/**
 * @brief Checks for duplicate integers in array.
 * @param array, @param size.
 */
int					check_duplicates(int *array, int size);

/**
 * @brief Frees a dynamically allocated split array.
 * @param arr The array to free.
 */
void				free_split(char **arr);

/**
 * @brief Finds position of index in stack.
 * @param stack, @param index_limit.
 */
int					find_position(t_stack *stack, int index_limit);

/**
 * @brief Initializes program environment/context.
 * @param argc, @param argv, @param ctx pointer.
 */
int					init_environment(int argc, char **argv, t_context *ctx);

/**
 * @brief Orchestrates the sorting process.
 * @param a, @param b, @param f, @param in.
 */
void				run_sorting(t_stack *a, t_stack *b, t_flags *f,
						t_input *in);

/**
 * @brief Initializes and fills stack A.
 * @param a, @param argc, @param argv, @param in.
 */
int					init_and_fill_stack(t_stack *a, int argc, char **argv,
						t_input *in);

/**
 * @brief Cleans up memory used by stacks.
 * @param a, @param b.
 */
void				cleanup(t_stack *a, t_stack *b);

#endif
