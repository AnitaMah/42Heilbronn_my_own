/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pasring.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 15:54:03 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/26 12:39:23 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/**
 * Counts the number of words in a NULL-terminated string array.
 * Iterates through the split array to determine the total word count.
 * @param split The array of strings to be counted.
 * @return The integer count of words found in the array.
 */

int	count_words_in_split(char **split)
{
	int	count;

	count = 0;
	while (split[count])
		count++;
	return (count);
}
