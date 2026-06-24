/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* new_pasring.c                                      :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/06/15 15:54:03 by anmakhov          #+#             */
/* Updated: 2026/06/15 15:54:04 by anmakhov         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/*
** count_words_in_split - Counts the number of strings in a NULL-terminated array.
** @split: The pointer to the array of strings (like those returned by ft_split).
**
** Iterates through the array and returns the total number of elements before
** the NULL terminator.
*/
int count_words_in_split(char **split)
{
    int count;

    count = 0;
    while (split[count])
        count++;
    return (count);
}