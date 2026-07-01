/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 17:43:53 by username          #+#    #+#             */
/*   Updated: 2026/03/18 18:40:38 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

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

int	ft_total_len(int size, char **strs, char *sep)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (i < size)
	{
		len += ft_strlen(strs[i]);
		if (i != size - 1)
		{
			len += ft_strlen(sep);
		}
		i++;
	}
	return (len);
}

char	*ft_strcat(char *dest, char *src)
{
	int	j;
	int	i;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	char	*res;
	int		i;

	if (size == 0)
	{
		res = malloc(1);
		res[0] = '\0';
		return (res);
	}
	res = (char *) malloc(sizeof(char) * ft_total_len(size, strs, sep));
	if (!res)
		return (NULL);
	res[0] = '\0';
	i = 0;
	while (i < size)
	{
		ft_strcat(res, strs[i]);
		if (i != size - 1)
		{
			ft_strcat(res, sep);
		}
		i++;
	}
	return (res);
}
