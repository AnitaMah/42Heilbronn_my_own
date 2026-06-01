/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 22:01:29 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/01 22:01:29 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>

/*
** =========================
**        STRUCTURES
** =========================
*/

/*
** Node of the stack (doubly linked list)
** Represents one element in stack A or B.
*/
typedef struct s_node
{
	int				value;   // original value from input
	int				index;   // normalized index used for sorting logic
	struct s_node	*next;   // next element in stack
	struct s_node	*prev;   // previous element in stack
}					t_node;

/*
** Stack structure
** Represents a full stack (A or B).
*/
typedef struct s_stack
{
	t_node			*top;        // first element (top of stack)
	t_node			*bottom;     // last element (bottom of stack)
	int				size;        // number of elements in stack
	int				chunk_size;  // used in chunk-based sorting algorithm
}					t_stack;

/*
** =========================
**        OPERATIONS
** =========================
*/

/*
** SWAP OPERATIONS
** Swap the first two elements of a stack.
** If stack has less than 2 elements -> do nothing.
*/
void	sa(t_stack *a);
void	sb(t_stack *b);
void	ss(t_stack *a, t_stack *b);

/*
** PUSH OPERATIONS
** Move the top element from one stack to another.
** pa: B -> A
** pb: A -> B
*/
void	pa(t_stack *a, t_stack *b);
void	pb(t_stack *a, t_stack *b);

/*
** ROTATE OPERATIONS
** Shift all elements up by one position.
** First element becomes last.
*/
void	ra(t_stack *a);
void	rb(t_stack *b);
void	rr(t_stack *a, t_stack *b);

/*
** REVERSE ROTATE OPERATIONS
** Shift all elements down by one position.
** Last element becomes first.
*/
void	rra(t_stack *a);
void	rrb(t_stack *b);
void	rrr(t_stack *a, t_stack *b);

/*
** =========================
**        SORT LOGIC
** =========================
*/

/*
** quicksort
** Sorts an integer array.
** Used to normalize values into indexes for efficient sorting.
*/
void	quicksort(int *arr, int left, int right);

/*
** normalize_index
** Replaces each value in stack with its rank (index)
** based on sorted order of all values.
*/
void	normalize_index(t_stack *a);

/*
** chunk_sort
** Main sorting algorithm for push_swap.
** Divides data into chunks and moves elements between stacks.
*/
void	chunk_sort(t_stack *a, t_stack *b);

/*
** bring_to_top
** Rotates stack until the target node becomes the top element.
*/
void	bring_to_top(t_stack *stack, t_node *target);

/*
** restore_to_a
** Moves all elements from stack B back to stack A
** in correct order.
*/
void	restore_to_a(t_stack *a, t_stack *b);

#endif
