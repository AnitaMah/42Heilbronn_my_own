/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 10:08:05 by username          #+#    #+#             */
/*   Updated: 2026/03/18 12:34:17 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_copy(char *dest, char *str)
{
	int	iter;

	iter = 0;
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
	int		length;

	length = ft_strlen(src);
	dest = malloc((sizeof(char)) * (length));
	if (dest == NULL)
		return (NULL);
	dest = ft_copy(dest, src);
	return (dest);
}

// int	main(void)
// {
// 	char	*src = "12345";
// 	char	*str = ft_strdup(src);

// 	printf("%s", str);
// 	return (0);
// }
