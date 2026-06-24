/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* parse_args_utils.c                                 :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: jdhamoda <jdhamoda@student.42heilbronn.    +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/06/16 16:46:35 by jdhamoda          #+#    #+#             */
/* Updated: 2026/06/16 18:12:37 by jdhamoda         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/*
 * is_valid_split - Checks if the split array is valid and not empty.
 * If invalid, it frees the memory allocated for the split.
 * @split: The array of strings to validate.
 * Return: 1 if valid, 0 otherwise.
 */
static int  is_valid_split(char **split)
{
    if (!split || !split[0])
    {
        free_split(split);
        return (0);
    }
    return (1);
}

/*
 * is_flag_arg - Checks if a given string argument is a flag (starts with "--").
 * @s: The string argument to check.
 * Return: 1 if it is a flag, 0 otherwise.
 */
static int  is_flag_arg(char *s)
{
    return (s && s[0] == '-' && s[1] == '-');
}

/*
 * process_split - Handles the splitting of an argument string and performs 
 * either counting or data extraction based on the mode.
 * @arg: The input string argument to be split.
 * @nums: Pointer to the array where numbers are stored.
 * @k: Pointer to the current index in the numbers array.
 * @mode: Mode selector (0 for counting, 1 for filling).
 * Return: The result of the operation (count or success status).
 */
static int  process_split(char *arg, int *nums, int *k, int mode)
{
    char    **split;
    int     result;

    split = ft_split(arg, ' ');
    if (!is_valid_split(split))
        return (0);
    if (mode == 0)
        result = count_words_in_split(split);
    else
        result = fill_single_split(split, nums, k);
    free_split(split);
    return (result);
}

/*
 * handle_args - Iterates through command-line arguments to either count 
 * total elements or fill the integer array.
 * @argc: Number of arguments.
 * @argv: Array of argument strings.
 * @nums: Pointer to the destination array.
 * @mode: Mode selector (0 for counting total, 1 for parsing values).
 * Return: Total count (if mode 0) or success status (if mode 1).
 */
int handle_args(int argc, char **argv, int *nums, int mode)
{
    int i;
    int total;
    int k;

    i = 1;
    total = 0;
    k = 0;
    while (i < argc)
    {
        if (is_flag_arg(argv[i]))
        {
            i++;
            continue ;
        }
        if (mode == 0)
            total += process_split(argv[i], nums, &k, 0);
        else if (!process_split(argv[i], nums, &k, 1))
            return (0);
        i++;
    }
    if (mode == 0)
        return (total);
    return (1);
}
