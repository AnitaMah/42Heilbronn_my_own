/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03                                #+#    #+#             */
/*   Updated: 2026/06/03                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** =========================
**      CORE LOGIC
** =========================
*/

/*
** Frees all nodes in stack and resets structure
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