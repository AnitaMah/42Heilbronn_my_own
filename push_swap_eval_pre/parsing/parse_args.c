/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 16:18:20 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/26 13:17:52 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/**
 * @brief Parses command-line arguments into an integer array.
 * @param argc The count of command-line arguments.
 * @param argv The array of argument strings.
 * @param size Pointer to store the number of integers parsed.
 * @return Dynamically allocated integer array, or NULL on error.
 */

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
