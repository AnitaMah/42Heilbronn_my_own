/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* check_errors.c                                     :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/06/15 16:17:59 by anmakhov          #+#    #+#             */
/* Updated: 2026/06/15 16:18:00 by anmakhov         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/*
** check_duplicates - Checks for duplicate integers in an array.
** @array: The pointer to the array of integers to be checked.
** @size: The number of elements in the array.
**
** Iterates through the array and compares each element with the subsequent ones.
** Returns 1 if a duplicate is found, 0 otherwise.
*/
int check_duplicates(int *array, int size)
{
    int i;
    int j;

    i = 0;
    while (i < size)
    {
        j = i + 1;
        while (j < size)
        {
            if (array[i] == array[j])
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}