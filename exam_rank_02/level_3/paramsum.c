/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paramsum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:37:42 by anmakhov          #+#    #+#             */
/*   Updated: 2026/05/27 17:40:46 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void print_digt(int nb)
{
    if (nb >= 10)
        print_digt(nb/10);
    write(1, &(char){nb % 10 + '0'}, 1);
}
int main(int argc, char **argv)
{
    (void)argv;
    int sum = argc - 1;

    print_digt(sum);
    write(1, "\n", 1);
    return (0);
}