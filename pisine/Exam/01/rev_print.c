/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 20:03:34 by username          #+#    #+#             */
/*   Updated: 2026/03/17 20:16:15 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strlen(char *str)
{
	int	iter = 0;

	while (str[iter])
	{
		iter++;
	}
	return ((iter)++);
}

void	print(char *str)
{
	int	iter = 0;

	while (str[iter])
	{
		write(1, &str[iter], 1);
		iter++;
	}
}

char	*reverse(char *str, int size)
{
	int	temp;
	int	iter = 0;

	while (iter < size / 2)
	{
		temp = str[iter];
		str[iter] = str[size - iter - 1];
		str[size - iter - 1] = temp;
		iter++;
	}
	return (str);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		int		size = ft_strlen(argv[1]);
		char	*str = reverse(argv[1], size);

		print(str);
	}
	write(1, "\n", 1);
}
