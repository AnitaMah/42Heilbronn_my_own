/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 14:01:41 by anmakhov          #+#    #+#             */
/*   Updated: 2026/05/28 14:07:41 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flood_fill.h"

void	fill(char **area, t_point size, t_point vec, char to_fill)
{
	if (vec.y < 0 || vec.y >= size.y || vec.x < 0 || vec.x >= size.x
		|| area[vec.y][vec.x] != to_fill)
		return ;
	area[vec.y][vec.x] = 'F';
	fill(area, size, (t_point){vec.x - 1, vec.y}, to_fill);
	fill(area, size, (t_point){vec.x + 1, vec.y}, to_fill);
	fill(area, size, (t_point){vec.x, vec.y - 1}, to_fill);
	fill(area, size, (t_point){vec.x, vec.y + 1}, to_fill);
}

void	flood_fill(char **area, t_point size, t_point begin)
{
	char	to_fill;

	to_fill = area[begin.y][begin.x];
	fill(area, size, begin, to_fill);
}
