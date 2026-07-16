/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 16:48:15 by anmakhov          #+#    #+#             */
/*   Updated: 2026/05/22 16:52:51 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(char *src)
{
	char	*res;
	int		len;
	int		iter;
	
	len = 0;
	while (src[len])
	{
		len++;
	}
	res = malloc (sizeof (char *) * (len + 1));
	if (!res)
	{
		return (NULL);
	}
	iter = 0; 
	while (src[iter])
	{
		res[iter] = src[iter];
		iter++;
	}
	res[iter] = '\0';
	return (res);
}
