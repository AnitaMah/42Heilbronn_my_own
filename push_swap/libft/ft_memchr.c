/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 10:46:31 by anmakhov          #+#    #+#             */
/*   Updated: 2026/04/28 12:41:24 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int char_vallue, size_t n)
{
	size_t				iter;
	unsigned char		ch;
	unsigned char		*clone_s;

	iter = 0;
	clone_s = (unsigned char *) s;
	ch = (unsigned char) char_vallue;
	while (iter < n)
	{
		if (clone_s[iter] == ch)
		{
			return (clone_s + iter);
		}
		iter++;
	}
	return (NULL);
}
