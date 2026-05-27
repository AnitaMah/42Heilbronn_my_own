/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lcm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:31:14 by anmakhov          #+#    #+#             */
/*   Updated: 2026/05/27 17:31:21 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	lcm(unsigned int a, unsigned int b)
{
	int	div;

	if (a == 0 || b == 0)
	{
		return (0);
	}
	div = 2;
	while (1)
	{
		if (a % div == 0 && b % div == 0)
			return (div);
		else if (div > a || div > b)
			return (1);
		div++;
	}
}
