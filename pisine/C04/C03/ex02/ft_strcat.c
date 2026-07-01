/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:36:01 by anmakhov          #+#    #+#             */
/*   Updated: 2026/03/05 12:46:50 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*ft_strcat(char *dest, char *src)
{
	int		j;
	int		i;

	i = 0;
	while (dest[i] != '\0')
		i ++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		j++;
		i ++;
	}
	dest[i] = '\0';
	return (dest);
}
// int main(void)
// {
// 	int	i;
// 	char 	dest[12] = "Hello";
// 	char	src[6] = "World";
// 	ft_strcat(dest, src);
// 	i = 0;
// 	while (dest[i] != '\0')
// 	{
// 		write(1, &dest[i], 1);
// 		i++;
// 	}
// }