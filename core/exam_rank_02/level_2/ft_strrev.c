/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 17:16:06 by anmakhov          #+#    #+#             */
/*   Updated: 2026/05/26 15:16:31 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strrev(char *str)
{
	int	len;
	int i;
	char temp;
	
	len = 0;
	while (str[len])
	{
		len++;
	}
	i = 0;
	while (i < len / 2)
	{
		temp = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = temp;
		i++;
	}
	return (str);
}

int main(int argv, char **argc)
{
	char *str;
	if (argv == 2)
	{
		str = ft_strrev(argc[1]);
	}	
	printf("%s", str);
	return (0);
}