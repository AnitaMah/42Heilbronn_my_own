/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_to_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:06:30 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/18 14:49:09 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

void	restore_to_a(t_stack *a, t_stack *b, t_flags *apply)
{
	t_node	*max;

	while (b->size > 0)
	{
		max = find_max(b);
		if (!max)
			break ;
		if (b->top != max)
			bring_to_top(b, max, apply);
		pa(a, b, apply);
	}
}
