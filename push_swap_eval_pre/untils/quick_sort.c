/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 13:46:10 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/26 12:42:28 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/**
 * Partitions the array around a pivot for the quicksort algorithm.
 * Reorganizes elements smaller than the pivot to the left side.
 * @param arr The array of integers to be partitioned.
 * @param left Starting index of the partition.
 * @param right Ending index (pivot) of the partition.
 * @return The final index position of the pivot element.
 */

int	partition(int *arr, int left, int right)
{
	int	i;
	int	j;
	int	tmp;
	int	pivot;

	pivot = arr[right];
	i = left;
	j = left;
	while (j < right)
	{
		if (arr[j] < pivot)
		{
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
		}
		j++;
	}
	tmp = arr[i];
	arr[i] = arr[right];
	arr[right] = tmp;
	return (i);
}

/**
 * Recursively sorts an integer array using the quicksort algorithm.
 * Divides the array into sub-arrays based on the pivot index.
 * @param arr The array of integers to be sorted.
 * @param left Starting index for the sort range.
 * @param right Ending index for the sort range.
 */

void	quicksort(int *arr, int left, int right)
{
	int	pivot_index;

	if (left >= right)
		return ;
	pivot_index = partition(arr, left, right);
	quicksort(arr, left, pivot_index - 1);
	quicksort(arr, pivot_index + 1, right);
}
