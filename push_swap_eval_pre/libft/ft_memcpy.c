/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:14:14 by anmakhov          #+#    #+#             */
/*   Updated: 2026/04/29 15:15:36 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *source, size_t counter)
{
	unsigned char	*clone_dest;
	unsigned char	*clone_source;
	size_t			iter;

	if (!dest && !source)
		return (NULL);
	clone_dest = (unsigned char *) dest;
	clone_source = (unsigned char *) source;
	iter = 0;
	while (iter < counter)
	{
		clone_dest[iter] = clone_source[iter];
		iter++;
	}
	return (dest);
}
