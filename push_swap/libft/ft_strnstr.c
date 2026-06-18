/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:34:59 by anmakhov          #+#    #+#             */
/*   Updated: 2026/04/29 14:48:22 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *to_find, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	len;

	if (to_find[0] == '\0')
		return ((char *) s1);
	len = 0;
	while (to_find[len] != '\0')
		len++;
	i = 0;
	while (s1[i] != '\0' && i < n)
	{
		j = 0;
		while (s1[i + j] == to_find[j] && to_find[j] != '\0' && i + j < n)
			j++;
		if (j == len)
			return ((char *) &s1[i]);
		i++;
	}
	return (NULL);
}
