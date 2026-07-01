/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:46:48 by username          #+#    #+#             */
/*   Updated: 2026/04/30 15:41:46 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t numbers_of_ellements, size_t element_size)
{
	char	*pointer;

	if (!numbers_of_ellements || !element_size)
	{
		return (malloc(0));
	}
	if (element_size > __SIZE_MAX__ / numbers_of_ellements)
		return (NULL);
	pointer = malloc(numbers_of_ellements * element_size);
	if (pointer)
	{
		ft_bzero(pointer, numbers_of_ellements * element_size);
	}
	return (pointer);
}
