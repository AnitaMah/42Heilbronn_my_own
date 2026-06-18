/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:30:53 by anmakhov          #+#    #+#             */
/*   Updated: 2026/04/29 15:01:05 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

static size_t	num_len(int nb)
{
	size_t	len;

	len = 1;
	while (nb != 0)
	{
		nb /= 10;
		if (nb != 0)
			len++;
	}
	return (len);
}

char	*ft_itoa(int nb)
{
	long int	clone_nb;
	size_t		len;
	char		*res;

	if (nb == 0)
		return (ft_strdup("0"));
	clone_nb = nb;
	len = num_len(nb);
	if (nb < 0)
	{
		clone_nb *= -1;
		len++;
	}
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[len] = '\0';
	while (clone_nb > 0)
	{
		res[--len] = (clone_nb % 10) + '0';
		clone_nb /= 10;
	}
	if (nb < 0)
		res[0] = '-';
	return (res);
}
