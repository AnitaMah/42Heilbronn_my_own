/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:27:21 by anmakhov          #+#    #+#             */
/*   Updated: 2026/04/27 15:55:47 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int char_vallue, size_t size)
{
	unsigned char	*clone_dest;
	unsigned int	iter;
	char			vallue;

	iter = size;
	clone_dest = (unsigned char *) dest;
	vallue = char_vallue;
	while (iter-- > 0)
	{
		clone_dest[iter] = vallue;
	}
	return (dest);
}
