#include "push_swap.h"

void	rr(t_stack *a, t_stack *b)
{
	rotate_stack(a);
	rotate_stack(b);
	write(1, "rr\n", 3);
}

void	rb(t_stack *b)
{
	rotate_stack(b);
	write(1, "rb\n", 3);
}

void	ra(t_stack *a)
{
	rotate_stack(a);
	write(1, "ra\n", 3);
}

static void	rotate_stack(t_stack *stack)
{
	t_node	*first;

	if (!stack || stack->size < 2)
		return ;
	first = stack->top;
	stack->top = first->next;
	stack->top->prev = NULL;
	first->next = NULL;
	first->prev = stack->bottom;
	stack->bottom->next = first;
	stack->bottom = first;
}
