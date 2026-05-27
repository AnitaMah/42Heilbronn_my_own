/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 16:44:31 by anmakhov          #+#    #+#             */
/*   Updated: 2026/05/20 16:53:15 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*ft_strcpy(char *s1, char *s2)
{
	int iter = 0;
	while (s2[iter])
	{
		s1[iter] = s2[iter];
		iter++;
	}
	s1[iter] = '\0';
	return (s1);
}

// int main(int argv, char **argc)
// {
// 	char *str;
// 	int iter = 0;
// 	if (argv == 3)
// 	{
// 		str = ft_strcpy(argc[1], argc[2]);
// 	}
// 	while (str[iter])
// 	{
// 		write (1, &str[iter], 1);
// 		iter++;
// 	}
// 	return (0);
// }