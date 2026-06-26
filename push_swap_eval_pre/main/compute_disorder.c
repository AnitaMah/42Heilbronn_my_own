/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_disorder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhamoda <jdhamoda@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 11:57:53 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/26 13:11:27 by jdhamoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/**
 * @file disorder_calculator.c
 * @brief Metric computation for tracking structural data order in push_swap.
 */

/**
 * @brief Calculates the inversion-based disorder metric of an integer array.
 * * Computes the ratio of actual mistakes (out-of-order pairs) relative to the 
 * maximum possible inversions in an array of the given size. A result of `0.0` 
 * means perfectly sorted, while `1.0` means completely reversed.
 *
 * @param arr The integer array to analyze.
 * @param size The total number of elements in the array.
 * @return A double between 0.0 and 1.0 representing the structural chaos level.
 */

double	compute_disorder(int *arr, int size)
{
	int	total;
	int	i;
	int	j;
	int	mistakes;

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
