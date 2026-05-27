/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 17:08:24 by anmakhov          #+#    #+#             */
/*   Updated: 2026/05/20 17:18:53 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int ft_strlen(char *str)
{
    int iter = 0;
    while (str[iter])
        iter++;
    return (iter);
}

void ft_putstr(char *str)
{
    int iter = 0;
    while (str[iter])
    {
        write(1, &str[iter], 1);
        iter++;
    }
}

void print_rev(char *str)
{
    int iter = 0;
    char temp;
    int size = ft_strlen(str);
    while (iter < size/2)
    {
        temp = str[iter];
        str[iter] = str[size - iter - 1];
        str[size - iter - 1] = temp;
        iter++;
    }
    ft_putstr(str);
}

int main(int argv, char **argc)
{
    if (argv == 2)
    {
        print_rev(argc[1]);
    }
    write(1, "\n", 1);
    return (0);
}