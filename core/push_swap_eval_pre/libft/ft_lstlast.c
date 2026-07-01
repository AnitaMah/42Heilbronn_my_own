/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 15:31:47 by anmakhov          #+#    #+#             */
/*   Updated: 2026/04/28 15:37:43 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*clone_lst;

	if (!lst)
		return (NULL);
	clone_lst = lst;
	while (clone_lst->next)
	{
		clone_lst = clone_lst->next;
	}
	return (clone_lst);
}
