/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:12:03 by username          #+#    #+#             */
/*   Updated: 2026/03/17 16:39:56 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	*move_iter_after_pace(char *str, int *iter)
{
	while (str[*iter] == ' ')
	{
		(*iter)++;
	}
	return (iter);
}

void	print_the_first_words(char *str, int *iter)
{
	while (str[*iter] && (str[*iter] != ' ' && str[*iter] != '\t'))
	{
		write(1, &str[*iter], 1);
		(*iter)++;
	}
}

int	main(int argc, char **argv)
{
	int	iter = 0;

	if (argc == 2)
	{
		move_iter_after_pace(argv[1], &iter);
		print_the_first_words(argv[1], &iter);
	}
	write(1, "\n", 1);
	return (0);
}
