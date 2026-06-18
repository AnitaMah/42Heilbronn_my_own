/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 12:39:59 by anmakhov          #+#    #+#             */
/*   Updated: 2026/04/29 15:04:27 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	size_t	clone_nb;

	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		clone_nb = (size_t)(-(long) nb);
	}
	else
	{
		clone_nb = (size_t) nb;
	}
	if (clone_nb > 9)
	{
		ft_putnbr_fd((int)(clone_nb / 10), fd);
	}
	ft_putchar_fd((char)(clone_nb % 10 + '0'), fd);
}
