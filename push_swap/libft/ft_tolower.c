/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:54:12 by anmakhov          #+#    #+#             */
/*   Updated: 2026/04/28 11:49:25 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int char_vallue)
{
	if (char_vallue >= 'A' && char_vallue <= 'Z')
	{
		char_vallue = char_vallue + ('a' - 'A');
	}
	return (char_vallue);
}
