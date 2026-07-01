/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 10:08:05 by anmakhov         #+#    #+#             */
/*   Updated: 2026/04/27 15:56:15 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_copy(char *dest, const char *str, size_t len)
{
	size_t	iter;

	iter = 0;
	while (str[iter] && iter < len)
	{
		dest[iter] = str[iter];
		iter++;
	}
	dest[iter] = '\0';
	return (dest);
}

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		length;

	length = ft_strlen(src);
	dest = malloc((sizeof(char)) * (length + 1));
	if (!dest)
		return (NULL);
	dest = ft_copy(dest, src, length + 1);
	return (dest);
}
