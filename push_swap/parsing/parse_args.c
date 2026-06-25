/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhamoda <jdhamoda@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 16:18:20 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/16 18:48:34 by jdhamoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

int	*parse_args(int argc, char **argv, int *size)
{
	int	*nums;
	int	len;

	if (argc < 2)
		return (NULL);
	len = handle_args(argc, argv, NULL, 0);
	if (len <= 0)
		return (NULL);
	nums = malloc(sizeof(int) * len);
	if (!nums)
		return (NULL);
	if (!handle_args(argc, argv, nums, 1))
	{
		free(nums);
		return (NULL);
	}
	*size = len;
	return (nums);
}
