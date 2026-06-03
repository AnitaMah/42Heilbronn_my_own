/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03                                #+#    #+#             */
/*   Updated: 2026/06/03                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Initializes stack structure:
** - top = NULL
** - bottom = NULL
** - size = 0
** - chunk_size = 0
*/
void	init_stack(t_stack *a)
{
	if (!a)
		return ;
	a->top = NULL;
	a->bottom = NULL;
	a->size = 0;
	a->chunk_size = 0;
}