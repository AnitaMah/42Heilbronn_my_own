#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>

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
}					t_stack;

/* swap */
void				sa(t_stack *a);
void				sb(t_stack *b);
void				ss(t_stack *a, t_stack *b);

/* push */
void				pa(t_stack *a, t_stack *b);
void				pb(t_stack *a, t_stack *b);

/* rotate */
void				ra(t_stack *a);
void				rb(t_stack *b);
void				rr(t_stack *a, t_stack *b);

/* reverse rotate */
void				rra(t_stack *a);
void				rrb(t_stack *b);
void				rrr(t_stack *a, t_stack *b);

void				quicksort(int *arr, int left, int right);
void				normalize_index(t_stack *a);
void				chunk_sort(t_stack *a, t_stack *b);
void				bring_to_top(t_stack *stack, t_node *tagred);

#endif
