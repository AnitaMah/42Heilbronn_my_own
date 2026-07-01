/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 16:35:56 by anmakhov          #+#    #+#             */
/*   Updated: 2026/05/22 16:47:23 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	iter;
	size_t	j;
	
	iter = 0;
	j = 0;
	while (s[iter])
	{
		j = 0;
		while (reject[j])
		{
			if (s[iter] == reject[j])
			{
				return (iter);
			}
			j++;
		}
		iter++;
	}
	return (iter);
}