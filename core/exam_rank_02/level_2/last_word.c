/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 15:43:00 by anmakhov          #+#    #+#             */
/*   Updated: 2026/05/26 15:52:05 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	last_word_print(char *str)
{
	int	iter;

	if (!str || !str[0])
		return;
	iter = 0;
	while (str[iter])
		iter++;
	iter--;
	while(iter >= 0 && (str[iter] == ' ' || str[iter] == '\t'))
		iter--;
	while (iter >= 0 && str[iter] != ' ' && str[iter] != '\t')
		iter--;
	iter++;
	while (str[iter] && str[iter] != ' ' && str[iter] != '\t')
	{
		write(1, &str[iter], 1);
		iter++;
	}
	
}

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        last_word_print(argv[1]);
    }
    write (1, "\n", 1);
    return (0);
}