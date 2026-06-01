#include "push_swap.h"

void	restore_to_a(t_stack *a, t_stack *b)
{
	while (b->size > 0)
	{
		pa(a, b);
	}
}

void	bring_to_top(t_stack *a, t_node *min)
{
	int		pos;
	int		size;
	t_node	*current;

	pos = 0;
	current = a->top;
	while (current != min)
	{
		current = current->next;
		pos++;
	}
	size = a->size;
	if (pos <= size / 2)
	{
		while (a->top != min)
			ra(a);
	}
	else
	{
		while (a->top != min)
			rra(a);
	}
}

t_node	*find_min(t_stack *a)
{
	t_node	*min;
	t_node	*current;

	if (!a || !a->top)
		return (NULL);
	current = a->top;
	min = a->top;
	while (current)
	{
		if (current->value < min->value)
			min = current;
		current = current->next;
	}
	return (min);
}

void	selections_sort_addaptation(t_stack *a, t_stack *b)
{
	t_node	*min;

	while (a->size > 0)
	{
		min = find_min_node(a);
		if (!min)
			return ;
		bring_to_top(a, min);
		pb(a, b);
	}
	restore_to_a(a, b);
}
