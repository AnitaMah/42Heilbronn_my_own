/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 18:45:35 by anmakhov          #+#    #+#             */
/*   Updated: 2026/05/20 18:47:19 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *s1, char *s2)
{
	int	iter;

	iter = 0;
	while (s1[iter] && s1[iter] == s2[iter])
	{
		iter++;
	}
	return ((unsigned char ) s1[iter] - (unsigned char) s2[iter]);
}
