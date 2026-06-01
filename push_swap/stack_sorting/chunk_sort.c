#include "push_swap.h"

t_node	*find_max(t_stack *b)
{
	t_node	*current;
	t_node	*max;

	if (!b || !b->top)
		return (NULL);
	current = b->top;
	max = b->top;
	while (current)
	{
		if (current->index > max->index)
			max = current;
		current = current->next;
	}
	return (max);
}
void	restore_to_a(t_stack *a, t_stack *b)
{
	t_node	*max;

	while (b->size > 0)
	{
		max = find_max(b);
		bring_to_top(b, max);
		pa(a, b);
	}
}

void	push_chunks(t_stack *a, t_stack *b)
{
	int	max;
	int	pushed;

	pushed = 0;
	max = a->chunk_size;
	while (a->size > 0)
	{
		if (a->top->index <= max)
		{
			pb(a, b);
			pushed++;
		}
		else
			ra(a);
		if (pushed == a->chunk_size)
		{
			max += a->chunk_size;
			pushed = 0;
		}
	}
}
void	init_chunks(t_stack *a)
{
	a->chunk_size = a->size / 5;
	if (a->chunk_size < 1)
		a->chunk_size = 1;
}
void	chunk_sort(t_stack *a, t_stack *b)
{
	normalize_index(a);
	init_chunks(a);
	push_chunks(a, b);
	restore_to_a(a, b);
}
