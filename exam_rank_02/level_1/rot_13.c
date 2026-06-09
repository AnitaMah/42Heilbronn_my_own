/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_13.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 13:36:48 by username          #+#    #+#             */
/*   Updated: 2026/06/08 13:32:37 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr(char *str)
{
	while (*str)
	{
		write(1, str, 1);
		str++;
	}
}

char	*ft_changer(char *str)
{
	int	iter;

	iter = 0;
	while (str[iter])
	{
		if ((str[iter] >= 'A' && str[iter] <= 'M') || (str[iter] >= 'a'
				&& str[iter] <= 'm'))
		{
			str[iter] = str[iter] + 13;
		}
		else if ((str[iter] >= 'N' && str[iter] <= 'Z') || (str[iter] >= 'n'
				&& str[iter] <= 'z'))
		{
			str[iter] = str[iter] - 13;
		}
		iter++;
	}
	return (str);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		ft_putstr(ft_changer(argv[1]));
	}
	write(1, "\n", 1);
}
