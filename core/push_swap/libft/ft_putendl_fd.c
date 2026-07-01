/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 12:38:05 by anmakhov          #+#    #+#             */
/*   Updated: 2026/04/27 15:55:55 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	iter;

	iter = 0;
	while (s[iter])
	{
		write(fd, &s[iter], 1);
		iter++;
	}
	write(fd, "\n", 1);
}
