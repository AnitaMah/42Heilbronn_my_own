/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* parse_args.c                                       :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: jdhamoda <jdhamoda@student.42heilbronn.    +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/06/15 16:18:20 by anmakhov          #+#    #+#             */
/* Updated: 2026/06/16 18:48:34 by jdhamoda         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/*
** parse_args - Parses command line arguments into an array of integers.
** @argc: The number of arguments.
** @argv: The array of argument strings.
** @size: Pointer to store the number of integers parsed.
**
** Allocates memory for the integer array, validates the input format,
** and populates the array using the helper function handle_args.
** Returns the pointer to the array if successful, or NULL on error.
*/
int *parse_args(int argc, char **argv, int *size)
{
    int *nums;
    int len;

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