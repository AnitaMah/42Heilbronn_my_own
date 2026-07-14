/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rstr_capitalizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 20:24:59 by anmakhov          #+#    #+#             */
/*   Updated: 2026/05/27 20:25:00 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	rstr_capitalizer(char *str)
{
	int	iter;

	iter = 0;
	while (str[iter])
	{
		if (str[iter] >= 'A' && str[iter] <= 'Z')
			str[iter] += 32;
		if ((str[iter] >= 'a' && str[iter] <= 'z') && (str[iter + 1] == ' '
				|| str[iter + 1] == '\t' || str[iter + 1] == '\0'))
		{
			str[iter] -= 32;
		}
		write(1, &str[iter], 1);
		iter++;
	}
}

int	main(int argc, char **argv)
{
	int	size;
	int	iter;

	iter = 1;
	size = argc;
	while (iter < size)
	{
		rstr_capitalizer(argv[iter]);
		write(1, "\n", 1);
		iter++;
	}
	write(1, "\n", 1);
	return (0);
}
