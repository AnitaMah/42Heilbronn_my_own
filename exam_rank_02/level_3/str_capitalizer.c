/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_capitalizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 20:17:19 by anmakhov          #+#    #+#             */
/*   Updated: 2026/05/27 20:19:15 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	str_capitalizer(char *str)
{
	int	iter;

	iter = 0;
	while (str[iter])
	{
		if (str[iter] >= 'A' && str[iter] <= 'Z')
			str[iter] += 32;
		if ((str[iter] >= 'a' && str[iter] <= 'z') && (iter == 0 || str[iter
				- 1] == 32 || (str[iter - 1] >= 9 && str[iter - 1] <= 13)))
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

	if (argc == 1)
	{
		write(1, "\n", 1);
		return (0);
	}
	iter = 1;
	size = argc;
	while (iter < size)
	{
		str_capitalizer(argv[iter]);
		write(1, "\n", 1);
		iter++;
	}
	return (0);
}
