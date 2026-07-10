/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotone.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 13:36:48 by username          #+#    #+#             */
/*   Updated: 2026/07/10 14:16:46 by anmakhov         ###   ########.fr       */
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
		if ((str[iter] >= 'a' && str[iter] <= 'y') || (str[iter] >= 'A'
				&& str[iter] <= 'Y'))
		{
			str[iter] += 1;
		}
		else if (str[iter] == 'z')
			str[iter] = 'a';
		else if (str[iter] == 'Z')
			str[iter] = 'A';
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
