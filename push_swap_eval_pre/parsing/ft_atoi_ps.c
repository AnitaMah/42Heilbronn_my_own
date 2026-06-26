/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_ps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 16:45:20 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/26 13:17:19 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/**
 * @brief Skips leading whitespace characters in the string.
 * @param s The string to scan.
 * @param i Pointer to the current index in the string.
 */

static void	skip_spaces(const char *s, int *i)
{
	while (s[*i] == ' ' || (s[*i] >= 9 && s[*i] <= 13))
		(*i)++;
}

/**
 * @brief Checks for and processes the sign of the number.
 * @param s The string to scan.
 * @param i Pointer to the current index in the string.
 * @return 1 for positive, -1 for negative.
 */

static int	handle_sign(const char *s, int *i)
{
	int	sign;

	sign = 1;
	if (s[*i] == '-' || s[*i] == '+')
	{
		if (s[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

/**
 * @brief Parses numerical digits and checks for integer overflow.
 * @param s The string to parse.
 * @param i Pointer to the current index.
 * @param error Pointer to error flag.
 * @param sign The sign of the number.
 * @return The parsed long value.
 */

static long	parse_digits(const char *s, int *i, int *error, int sign)
{
	long	result;

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

/**
 * @brief Converts a string to an integer with error checking for overflows.
 * @param s The string to be converted.
 * @param error Pointer to an integer for error status (set to 1 on failure).
 * @return The converted integer value, or 0 if an error occurred.
 */

int	ft_atoi_ps(const char *s, int *error)
{
	int		i;
	int		sign;
	long	value;

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
