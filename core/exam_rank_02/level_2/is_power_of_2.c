/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_power_of_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 15:31:52 by anmakhov          #+#    #+#             */
/*   Updated: 2026/05/26 15:31:54 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	is_power_of_2(unsigned int n)
{
	if (n == 0)
		return (0);
	if (n & (n - 1))
		return (0);
	return (1);
}

int main(int argc, char **argv)
{
	int nb;
	if (argc == 2)
	{
		nb = atoi(argv[1]);
		if (is_power_of_2(nb))
		{
			printf("This is power of 2");
		}
		else
		{
			printf("This number is not power of 2");
		}
	}
	return (0);
}