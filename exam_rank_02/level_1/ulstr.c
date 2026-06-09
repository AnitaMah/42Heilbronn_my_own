/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ulstr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 10:20:38 by username          #+#    #+#             */
/*   Updated: 2026/06/08 13:57:37 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr(const char *str)
{
	int	iter;

	iter = 0;
	while (str[iter])
	{
		write(1, &str[iter], 1);
		iter++;
	}
}

void	ulstr(char *str)
{
	int	iter;

	iter = 0;
	while (str[iter])
	{
		if (str[iter] >= 'a' && str[iter] <= 'z')
			str[iter] -= 32;
		else if (str[iter] >= 'A' && str[iter] <= 'Z')
			str[iter] += 32;
		iter++;
	}
	ft_putstr(str);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		ulstr(argv[1]);
	}
	write(1, "\n", 1);
	return (0);
}
