/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:56:59 by anmakhov          #+#    #+#             */
/*   Updated: 2026/04/28 11:58:57 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int char_vallue)
{
	unsigned char	ch;
	int				iter;

	iter = 0;
	ch = (unsigned char) char_vallue;
	if (ch == '\0')
	{
		iter = ft_strlen(str);
		return ((char *)str + iter++);
	}
	while (str[iter] != 0)
	{
		if (str[iter] == ch)
		{
			return ((char *) str + iter);
		}
		iter++;
	}
	return (NULL);
}
