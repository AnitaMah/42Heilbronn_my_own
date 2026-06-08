/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_13.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 13:36:48 by username          #+#    #+#             */
/*   Updated: 2026/03/18 09:56:16 by anmakhov         ###   ########.fr       */
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
	int		iter = 0;
	char	*clone = str;

	while (clone[iter])
	{
		if ((clone[iter] >= 'A' && clone[iter] <= 'M')
				|| (clone[iter] >= 'a' && clone[iter] <= 'm'))
		{
			clone[iter] = clone[iter] + 13;
		}
		else if ((clone[iter] >= 'N' && clone[iter] <= 'Z')
				|| (clone[iter] >= 'n' && clone[iter] <= 'z'))
		{
			clone[iter] = clone[iter] - 13;
		}
		iter++;
	}
	return (str);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		ft_putstr(argv[1]);
		write(1, "\n", 1);
		ft_putstr(ft_changer(argv[1]));
	}
	else
		write(1, "\n", 1);
	write(1, "\n", 1);
}
