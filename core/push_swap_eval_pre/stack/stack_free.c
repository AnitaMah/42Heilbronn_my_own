/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 11:14:39 by jdhamoda          #+#    #+#             */
/*   Updated: 2026/06/26 13:08:00 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/**
 * @brief Frees all nodes in the stack and resets stack members.
 * @param a The stack to be deallocated and cleared.
 */

void	free_stack(t_stack *a)
{
	t_node	*cur;
	t_node	*next;

	if (!a)
		return ;
	cur = a->top;
	while (cur)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
	a->top = NULL;
	a->bottom = NULL;
	a->size = 0;
	a->chunk_size = 0;
}
