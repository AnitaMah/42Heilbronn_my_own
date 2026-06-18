/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:53:42 by anmakhov          #+#    #+#             */
/*   Updated: 2026/04/29 14:44:49 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			iter;
	unsigned char	*cl_s1;
	unsigned char	*cl_s2;

	cl_s1 = (unsigned char *) s1;
	cl_s2 = (unsigned char *) s2;
	iter = 0;
	while (iter < n)
	{
		if (cl_s1[iter] != cl_s2[iter])
			return (cl_s1[iter] - cl_s2[iter]);
		iter++;
	}
	return (0);
}
