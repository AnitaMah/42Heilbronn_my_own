/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:48:23 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/02 12:48:47 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

void	save_case(int *arr, int size, char *file)
{
	FILE	*f;
	int		i;

	f = fopen(file, "w");
	i = 0;
	while (i < size)
	{
		fprintf(f, "%d ", arr[i]);
		i++;
	}
	fclose(f);
}
