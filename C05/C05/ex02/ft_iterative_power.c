/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:59:01 by anmakhov          #+#    #+#             */
/*   Updated: 2026/03/05 15:47:46 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_power(int nb, int power)
{
	int	i;
	int	nb_i;

	if (power < 0)
		return (0);
	else if (power == 0)
		return (1);
	i = 1;
	nb_i = nb;
	while (i < power)
	{
		nb *= nb_i;
		i++;
	}
	return (nb);
}
