/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 16:50:24 by anmakhov          #+#    #+#             */
/*   Updated: 2026/04/27 15:55:42 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				iter;
	size_t				clone_len;

	d = (unsigned char *) dest;
	s = (const unsigned char *) src;
	clone_len = len;
	iter = 0;
	if (!dest && !src)
		return (NULL);
	if (d < s)
	{
		while (iter < len)
		{
			d[iter] = s[iter];
			iter++;
		}
	}
	else
	{
		while (clone_len--)
			d[clone_len] = s[clone_len];
	}
	return (dest);
}
