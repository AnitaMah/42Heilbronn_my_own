/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:59:42 by anmakhov          #+#    #+#             */
/*   Updated: 2026/03/04 18:19:35 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <unistd.h>

char	*ft_strncat(char *dest, char *src, unsigned int n)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	i = 0;
	while (dest[i] != '\0')
		i ++;
	j = 0;
	k = 0;
	while (k < n && src [j] != '\0')
	{
		dest[i] = src[j];
		i ++;
		j++;
		k++;
	}
	dest[i] = '\0';
	return (dest);
}

// int main(void)
// {
// 	char dest[10] = "Hello";
// 	char src[5]="World";
// 	int n = 3;
// 	ft_strncat(dest, src, n);
// 	int i = 0;
// 	while (dest[i] != '\0')
// 	{
// 		write(1, &dest[i], 1);
// 		i++;
// 	}
// }
