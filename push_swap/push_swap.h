/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 22:01:29 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/03                                ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>

/*
** =========================================================
**                      STACK NODE
** =========================================================
**
** Doubly linked list node used as element of stack A / B.
** Each node stores:
** - value: original integer
** - index: normalized index (used for radix / chunk sort)
** - next / prev: links for doubly linked list
*/

typedef struct s_node
{
	int				value;
	int				index;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

/*
** =========================================================
**                      STACK STRUCTURE
** =========================================================
**
** Represents a stack (A or B).
** - top: first element
** - bottom: last element
** - size: number of elements
** - chunk_size: used in chunk-based sorting algorithms
*/

typedef struct s_stack
{
	t_node	*top;
	t_node	*bottom;
	int		size;
	int		chunk_size;
}	t_stack;

/*
** =========================================================
**                      STACK OPS
** =========================================================
** Basic operations required by push_swap subject
*/

/* Swap operations */
void	sa(t_stack *a);
void	sb(t_stack *b);
void	ss(t_stack *a, t_stack *b);

/* Push operations */
void	pa(t_stack *a, t_stack *b);
void	pb(t_stack *a, t_stack *b);

/* Rotate operations (upwards) */
void	ra(t_stack *a);
void	rb(t_stack *b);
void	rr(t_stack *a, t_stack *b);

/* Reverse rotate operations (downwards) */
void	rra(t_stack *a);
void	rrb(t_stack *b);
void	rrr(t_stack *a, t_stack *b);

/*
** =========================================================
**                      SORTING
** =========================================================
*/

/*
** Quicksort helper for normalization
** Used to sort array before assigning indexes
*/
void	quicksort(int *arr, int left, int right);

/*
** Converts values into normalized indexes (0..n)
** Important for radix / bitwise sorting
*/
void	normalize_index(t_stack *a);

/*
** Main chunk sorting algorithm (O(n√n) style)
*/
void	chunk_sort(t_stack *a, t_stack *b);

/*
** Finds the node with maximum index in a stack
*/
t_node	*find_max(t_stack *b);

/*
** Moves selected node to top of stack efficiently
*/
void	bring_to_top(t_stack *stack, t_node *target);

/*
** Restores elements from stack B back to A
*/
void	restore_to_a(t_stack *a, t_stack *b);

/*
** =========================
**        CORE FUNCTIONS
** =========================
*/

/*
** Initializes stack (sets top/bottom/size = 0/null)
*/
void	init_stack(t_stack *a);

/*
** Parses argv, fills stack A with integers
** returns 1 on success, 0 on error
*/
int		parse_args(t_stack *a, char **argv);

/*
** Checks if stack A is already sorted
** returns 1 if sorted, 0 otherwise
*/
int		is_sorted(t_stack *a);

/*
** Main sorting dispatcher (chooses algorithm)
*/
void	sort_stack(t_stack *a, t_stack *b);

/*
** Frees all memory used by stack
*/
void	free_stack(t_stack *a);

#endif
