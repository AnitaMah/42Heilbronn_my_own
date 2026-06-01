#include "push_swap.h"

void	process_bit(t_stack *a, t_stack *b, int bit)
{
	int	size;
	int	i;

	size = a->size;
	i = 0;
	while (i < size)
	{
		if (((a->top->index >> bit) & 1) == 0)
			pb(a, b);
		else
			ra(a);
		i++;
	}
}

int	get_max_bits(t_stack *a)
{
	int		max;
	int		bits;
	t_node	*current;

	if (!a || !a->top)
		return (0);
	current = a->top;
	max = current->index;
	while (current)
	{
		if (current->index > max)
			max = current->index;
		current = current->next;
	}
	bits = 0;
	while ((max >> bits) != 0)
	{
		bits++;
	}
	return (bits);
}

void	radix_sort(t_stack *a, t_stack *b)
{
	int	max_bits;
	int	i;

	if (!a || !a->top)
		return ;
	normalize_index(a);
	max_bits = get_max_bits(a);
	i = 0;
	while (i < max_bits)
	{
		process_bit(a, b, i);
		restore_to_a(a, b);
		i++;
	}
}
