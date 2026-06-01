#include "push_swap.h"

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
