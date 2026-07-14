/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hidenp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 20:25:12 by anmakhov          #+#    #+#             */
/*   Updated: 2026/05/27 20:25:13 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>

void	hidenp(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s1[0] =='\0')
	{
		write(1, "1", 1);
		return ;
	}
	while (s2[j])
	{
		if (s1[i] == s2[j])
			i++;
		if (s1[i] == '\0')
		{
			write(1, "1", 1);
			return ;
		}
		j++;
	}
	write(1, "0", 1);
}

int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		hidenp(argv[1], argv[2]);
	}
	write(1, "\n", 1);
	return (0);
}
