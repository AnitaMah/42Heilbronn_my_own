/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 12:56:36 by anmakhov          #+#    #+#             */
/*   Updated: 2026/03/14 12:48:20 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_iterative_factorial(int nb)
{
	int	i;

	if (nb == 0 || nb == 1)
		return (1);
	else if (nb < 0)
		return (0);
	i = nb;
	while (i > 1)
	{
		nb *= --i;
	}
	return (nb);
}

// int main(void)
// {	printf("1, %i\n", ft_iterative_factorial(0));
// 	printf("120, %i\n", ft_iterative_factorial(5));

// 	return (0);
// }