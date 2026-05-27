/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 11:21:56 by anmakhov          #+#    #+#             */
/*   Updated: 2026/03/12 18:10:20 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*ft_strstr(char *s1, char *to_find)
{
	int	i;
	int	j;
	int	len;

	if (to_find[0] == '\0')
		return (s1);
	len = 0;
	while (to_find[len] != '\0')
		len++;
	i = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		while (s1[i + j] == to_find[j] && to_find[j] != '\0')
			j++;
		if (j == len)
			return (&s1[i]);
		i++;
	}
	return (NULL);
}

// int main(void)
// {
// 	char *s1 = "hello World";
// 	char *to_find = "world";
// 	char *p = ft_strstr(s1, to_find);
// 	while (*p != 0)
// 	{
// 		write(1, p, 1);
// 		p++;
// 	}
// 	return 0;
// }