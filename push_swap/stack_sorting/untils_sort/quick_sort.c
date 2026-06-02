/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:07:15 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/02 12:07:15 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	partition(int *arr, int left, int right)
{
	int	pivot;
	int	i;
	int	j;
	int	tmp;

	pivot = arr[(left + right) / 2];
	i = left;
	j = right;
	while (i <= j)
	{
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j)
		{
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	}
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
