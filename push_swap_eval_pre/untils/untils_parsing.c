/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* untils_parsing.c                                   :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: jdhamoda <jdhamoda@student.42heilbronn.    +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/06/15 16:22:11 by anmakhov          #             */
/* Updated: 2026/06/15 22:01:22 by jdhamoda         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/*
** free_split - Frees a NULL-terminated array of strings and its contents.
** @arr: The pointer to the array of strings to be freed.
*/
void    free_split(char **arr)
{
    int i;

    if (!arr)
        return ;
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

/*
** is_valid_number - Checks if a string represents a valid integer.
** @s: The input string.
**
** Returns 1 if the string contains only digits (optionally preceded by a sign),
** 0 otherwise.
*/
int is_valid_number(char *s)
{
    int i;

    i = 0;
    if (!s)
        return (0);
    while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
        i++;
    if (s[i] == '+' || s[i] == '-')
        i++;
    if (!s[i])
        return (0);
    while (s[i])
    {
        if (s[i] < '0' || s[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

/*
** count_args - Counts the number of elements in a NULL-terminated array.
** @args: The pointer to the array.
*/
int count_args(char **args)
{
    int i;

    i = 0;
    while (args[i])
        i++;
    return (i);
}

/*
** free_args_if_split - Frees the argument array if it was allocated via split.
** @argc: The argument count.
** @args: The array of strings.
*/
void    free_args_if_split(int argc, char **args)
{
    if (argc == 2)
        free_split(args);
}

/*
** fill_single_split - Validates and converts an array of strings to integers.
** @split: Array of strings.
** @nums: Target array to store integers.
** @k: Pointer to the current index in the numbers array.
**
** Returns 1 on success, 0 if an invalid number or overflow is encountered.
*/
int fill_single_split(char **split, int *nums, int *k)
{
    int j;
    int error;

    j = 0;
    while (split[j])
    {
        error = 0;
        if (!is_valid_number(split[j]))
            return (0);
        nums[*k] = ft_atoi_ps(split[j], &error);
        if (error)
            return (0);
        (*k)++;
        j++;
    }
    return (1);
}