/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 10:08:05 by username          #+#    #+#             */
/*   Updated: 2026/03/18 16:40:05 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//len
//cpy
//togeth

#include <stdlib.h>
#include <stdio.h>

int	ft_strlen(char *str)
{
	int	i = 0;

	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_copy(char *dest, char *str)
{
	int	iter;

	while (str[iter])
	{
		dest[iter] = str[iter];
		iter++;
	}
	dest[iter] = '\0';
	return (dest);
}

char	*ft_strdup(char *src)
{
	char	*dest;
	int		length = ft_strlen(src);

	dest = malloc((sizeof(char)) * (length));
	if (dest == NULL)
		return (NULL);
	dest = ft_copy(dest, src);
	return (dest);
}

int	main(void)
{
	char	*src = "12345";
	char	*str = ft_strdup(src);

	printf("%s", str);
	return (0);
}
