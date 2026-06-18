/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhamoda <jdhamoda@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 13:46:10 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/15 14:59:58 by jdhamoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

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

void	quicksort(int *arr, int left, int right)
{
	int	pivot_index;

	if (left >= right)
		return ;
	pivot_index = partition(arr, left, right);
	quicksort(arr, left, pivot_index - 1);
	quicksort(arr, pivot_index + 1, right);
}
