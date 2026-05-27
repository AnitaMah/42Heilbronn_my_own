/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 13:39:14 by anmakhov          #+#    #+#             */
/*   Updated: 2026/03/14 15:33:59 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i ++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

// int main (void)
// {
// 	char src[5] = "hello";
// 	char dest[10];
// 	int n = 3, i = 0;
// 	ft_strncpy(dest, src, n);
// 	while (dest[i] != '\0')
// 	{
// 		write(1, &dest[i], 1);
// 		i++;
// 	}
// 	return 0;
// }