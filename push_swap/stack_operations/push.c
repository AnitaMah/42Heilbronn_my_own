#include "../push_swap.h"

/* static helper FIRST */
static void push_stack(t_stack *src, t_stack *dest)
{
	t_node *tmp;

	if (!src->top)
		return;
	tmp = src->top;
	src->top = tmp->next;
	if (src->top)
		src->top->prev = NULL;
	else
		src->bottom = NULL;

	tmp->prev = NULL;
	tmp->next = dest->top;

	if (dest->top)
		dest->top->prev = tmp;
	else
		dest->bottom = tmp;

	dest->top = tmp;

	src->size--;
	dest->size++;
}

/* pb */
void pb(t_stack *a, t_stack *b)
{
	push_stack(a, b);
	write(1, "pb\n", 3);
}

/* pa */
void pa(t_stack *a, t_stack *b)
{
	push_stack(b, a);
	write(1, "pa\n", 3);
}
