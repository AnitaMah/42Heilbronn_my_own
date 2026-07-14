/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rrange.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:14:51 by anmakhov          #+#    #+#             */
/*   Updated: 2026/05/27 17:18:31 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int ft_abs(int nb)
{
	if (nb < 0)
	{
		return (-nb);
	}
	return (nb);
}

int	*ft_rrange(int start, int end)
{
	int	*res;
	int	size;
	int	iter;

	size = ft_abs(end - start) + 1;
	iter = 0;
	res = (int *)malloc(size *sizeof(int));
	if (!res)
	{
		return (NULL);
	}
	while (iter < size)
	{
		if (end <= start)
			res[iter] = end++;
		else if (end >= start)
			res[iter] = end--;
		iter++;
	}
	return (res);
}
