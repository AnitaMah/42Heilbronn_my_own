/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* compute_disorder.c                                 :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/06/12 11:57:53 by anmakhov          #+#    #+#             */
/* Updated: 2026/06/15 13:26:11 by anmakhov         ###   ########.fr       */
/* */
/* ************************************************************************** */

/*
** compute_disorder - Calculates the disorder coefficient (inversion ratio)
** of an integer array.
**
** @arr:  Pointer to the array of integers.
** @size: The number of elements in the array.
**
** This function compares every pair of elements and counts the inversions
** (cases where a preceding element is greater than a succeeding element).
** It returns the ratio of the number of inversions to the total number of 
** possible pairs as a double. Returns 0.0 if the array size is <= 1.
*/
double  compute_disorder(int *arr, int size)
{
    int total;
    int i;
    int j;
    int mistakes;

    i = 0;
    mistakes = 0;
    total = size * (size - 1) / 2;
    if (size <= 1)
        return (0.0);
    while (i < size)
    {
        j = i + 1;
        while (j < size)
        {
            if (arr[i] > arr[j])
                mistakes++;
            j++;
        }
        i++;
    }
    return ((double)mistakes / (double)total);
}