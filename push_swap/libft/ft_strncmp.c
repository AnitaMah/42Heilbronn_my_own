/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:33:11 by anmakhov          #+#    #+#             */
/*   Updated: 2026/04/28 12:08:37 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			iter;

	s1 = (unsigned char *) str1;
	s2 = (unsigned char *) str2;
	iter = 0;
	while (iter < n && (s1[iter] || s2[iter]))
	{
		if (s1[iter] != s2[iter])
			return (s1[iter] - s2[iter]);
		iter++;
	}
	return (0);
}
