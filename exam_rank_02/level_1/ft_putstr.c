/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 16:39:49 by anmakhov          #+#    #+#             */
/*   Updated: 2026/05/20 16:43:22 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void ft_putstr(char *str)
{
    int iter = 0;
    while (str[iter])
    {
        write(1, &str[iter], 1);
        iter++;
    }
}

// int main (int argv, char **argc)
// {
//     if (argv == 2)
//     {
//         ft_putstr(argc[1]);
//     }
//     return (0);
// }