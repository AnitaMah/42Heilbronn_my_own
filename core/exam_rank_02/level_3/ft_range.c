/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 20:25:55 by anmakhov          #+#    #+#             */
/*   Updated: 2026/05/27 20:25:56 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

int	*ft_range(int start, int end)
{
	int	*res;
	int	size;
	int	iter;

	size = ft_abs(start - end )+ 1;
	res = (int *)malloc(size *sizeof(int));
	if (!res)
	{
		return (NULL);
	}
	iter = 0;
	while (iter < size)
	{
		if (start <= end)
			res[iter] = start++;
		else if (start >= end)
			res[iter] = start--;
		iter++;
	}
	return (res);
}
