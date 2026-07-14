#include "ft_list.h"

void swap_int(int *a, int *b)
{
	int temp;

	temp = *a;*a = *b;
	*b = temp;
}

t_list  *sort_list(t_list *lst, int (*cmp)(int, int))
{
    t_list  *current;
    int     swapped;

    if (!lst || !cmp)
        return (lst);

    swapped = 1;
    while (swapped)
    {
        swapped = 0;
        current = lst;
        while (current && current->next)
        {
            if (cmp(current->data, current->next->data) == 0)
            {
                swap_int(&current->data, &current->next->data);
                swapped = 1;
            }
            current = current->next;
        }
    }
    return (lst);
}
