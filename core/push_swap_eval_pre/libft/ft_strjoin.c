/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 17:43:53 by anmakhov          #+#    #+#             */
/*   Updated: 2026/04/28 17:27:36 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*res;
	int		size_of_s1;
	int		size_of_s2;

	size_of_s1 = ft_strlen(s1);
	size_of_s2 = ft_strlen(s2);
	res = (char *) malloc(sizeof(char) * (size_of_s2 + size_of_s1 + 1));
	if (!res)
		return (NULL);
	ft_memcpy(res, s1, size_of_s1);
	ft_memcpy(res + size_of_s1, s2, size_of_s2 + 1);
	return (res);
}
