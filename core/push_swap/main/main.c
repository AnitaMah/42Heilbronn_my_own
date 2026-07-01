/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 13:48:01 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/17 14:22:43 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

static int	handle_error(void)
{
	write(2, "Error\n", 6);
	return (1);
}

void	cleanup(t_stack *a, t_stack *b)
{
	free_stack(a);
	free_stack(b);
}

int	init_and_fill_stack(t_stack *a, int argc, char **argv, t_input *in)
{
	in->arr = parse_args(argc, argv, &in->size);
	if (!in->arr)
		return (0);
	if (check_duplicates(in->arr, in->size))
	{
		free(in->arr);
		return (0);
	}
	if (!stack_from_array(a, in->arr, in->size))
	{
		free(in->arr);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_input		in;
	t_flags		flags;
	t_stack		a;
	t_stack		b;
	t_context	ctx;

	ctx = (t_context){&a, &b, &in, &flags};
	if (argc < 2)
		return (0);
	if (!init_environment(argc, argv, &ctx))
		return (handle_error());
	if (is_sorted(&a))
	{
		cleanup(&a, &b);
		free(in.arr);
		return (0);
	}
	run_sorting(&a, &b, &flags, &in);
	return (0);
}
