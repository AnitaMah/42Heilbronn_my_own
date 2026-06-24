/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* ft_atoi_ps.c                                       :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: jdhamoda <jdhamoda@student.42heilbronn.    +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/06/15 16:45:20 by anmakhov          #+#    #+#             */
/* Updated: 2026/06/15 21:46:42 by jdhamoda         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/*
** skip_spaces - Skips leading whitespace characters in the string.
** @s: The input string.
** @i: Pointer to the current index in the string.
*/
static void skip_spaces(const char *s, int *i)
{
    while (s[*i] == ' ' || (s[*i] >= 9 && s[*i] <= 13))
        (*i)++;
}

/*
** handle_sign - Detects and handles the sign (+ or -) of the number.
** @s: The input string.
** @i: Pointer to the current index.
**
** Returns 1 for positive (or no sign), -1 for negative.
*/
static int  handle_sign(const char *s, int *i)
{
    int sign;

    sign = 1;
    if (s[*i] == '-' || s[*i] == '+')
    {
        if (s[*i] == '-')
            sign = -1;
        (*i)++;
    }
    return (sign);
}

/*
** parse_digits - Converts string digits to a long integer and checks for overflow.
** @s: The input string.
** @i: Pointer to the current index.
** @error: Pointer to an error flag.
** @sign: The previously determined sign multiplier.
**
** Returns the parsed number as a long. Sets *error to 1 if non-digit 
** or overflow occurs.
*/
static long parse_digits(const char *s, int *i, int *error, int sign)
{
    long    result;

    result = 0;
    if (s[*i] < '0' || s[*i] > '9')
        return (*error = 1, 0);
    while (s[*i] >= '0' && s[*i] <= '9')
    {
        result = result * 10 + (s[*i] - '0');
        if (sign == 1 && result > 2147483647)
            return (*error = 1, 0);
        if (sign == -1 && result > 2147483648)
            return (*error = 1, 0);
        (*i)++;
    }
    return (result);
}

/*
** ft_atoi_ps - Custom Atoi implementation for push_swap with error handling.
** @s: The string to convert.
** @error: Pointer to an integer used to signal conversion failures.
**
** Parses a string to an integer, verifying that the entire string is a 
** valid number within the integer range. Returns the value or 0 on error.
*/
int ft_atoi_ps(const char *s, int *error)
{
    int     i;
    int     sign;
    long    value;

    i = 0;
    *error = 0;
    skip_spaces(s, &i);
    sign = handle_sign(s, &i);
    value = parse_digits(s, &i, error, sign);
    if (*error)
        return (0);
    if (s[i] != '\0')
        return (*error = 1, 0);
    return ((int)(value * sign));
}