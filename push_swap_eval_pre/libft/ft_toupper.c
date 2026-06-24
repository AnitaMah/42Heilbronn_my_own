/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:52:41 by anmakhov          #+#    #+#             */
/*   Updated: 2026/04/28 11:52:50 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int char_vallue)
{
	if (char_vallue >= 'a' && char_vallue <= 'z')
		char_vallue = char_vallue - ('a' - 'A');
	return (char_vallue);
}
