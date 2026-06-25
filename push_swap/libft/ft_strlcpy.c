/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 15:38:24 by anmakhov          #+#    #+#             */
/*   Updated: 2026/05/13 19:22:22 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*copy_of_src_to_dest(char *dest, const char *src, size_t size)
{
	size_t	iter;

	iter = 0;
	while (src[iter] != 0 && iter < size - 1)
	{
		dest[iter] = src[iter];
		iter++;
	}
	dest[iter] = '\0';
	return (dest);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	int		len;

	len = ft_strlen(src);
	if (size == 0)
	{
		return (len);
	}
	copy_of_src_to_dest(dest, src, size);
	return (len);
}
