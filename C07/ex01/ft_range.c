/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 17:27:12 by anmakhov          #+#    #+#             */
/*   Updated: 2026/03/12 17:37:25 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int	*dest;
	int	i;
	int	nb;

	if (min >= max)
		return (NULL);
	dest = malloc(sizeof(int) * (max - min));
	nb = min;
	i = 0;
	while (nb < max)
	{
		dest[i] = nb;
		nb++;
		i++;
	}
	return (dest);
}
