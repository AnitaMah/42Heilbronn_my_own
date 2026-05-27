/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:07:35 by anmakhov          #+#    #+#             */
/*   Updated: 2026/05/27 17:14:01 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	size = (start - end + 1);
	res = (int *)malloc(size);
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