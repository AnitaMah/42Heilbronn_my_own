/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03                                #+#    #+#             */
/*   Updated: 2026/06/03                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** =========================
**      UTILS
** =========================
*/

static int	ft_atoi_ps(const char *str, int *error)
{
	long	n;
	int		sign;

	n = 0;
	sign = 1;
	*error = 0;

	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (*str == '\0')
		return (*error = 1, 0);

	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (*error = 1, 0);
		n = n * 10 + (*str - '0');
		if ((n * sign) > 2147483647 || (n * sign) < -2147483648)
			return (*error = 1, 0);
		str++;
	}
	return ((int)(n * sign));
}

/*
** =========================
**      NODE OPS
** =========================
*/

static t_node	*new_node(int value)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->value = value;
	node->index = -1;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

static void	add_back(t_stack *a, t_node *node)
{
	if (!a->top)
	{
		a->top = node;
		a->bottom = node;
	}
	else
	{
		a->bottom->next = node;
		node->prev = a->bottom;
		a->bottom = node;
	}
	a->size++;
}

/*
** =========================
**      CHECKERS
** =========================
*/

static int	has_duplicate(t_stack *a, int value)
{
	t_node	*cur;

	cur = a->top;
	while (cur)
	{
		if (cur->value == value)
			return (1);
		cur = cur->next;
	}
	return (0);
}

/*
** =========================
**      MAIN PARSER
** =========================
*/

int	parse_args(t_stack *a, char **argv)
{
	int		i;
	int		value;
	int		error;
	t_node	*node;

	i = 0;
	while (argv[i])
	{
		value = ft_atoi_ps(argv[i], &error);
		if (error)
			return (0);
		if (has_duplicate(a, value))
			return (0);
		node = new_node(value);
		if (!node)
			return (0);
		add_back(a, node);
		i++;
	}
	return (1);
}