/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   untils_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 14:20:10 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/26 13:24:10 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/**
 * @brief Initializes stacks, parses flags, and populates stack A.
 * @param argc Argument count, argv argument vector, ctx Context struct.
 * @return 1 on success, 0 on initialization failure.
 */

int	init_environment(int argc, char **argv, t_context *ctx)
{
	parse_flags(argc, argv, ctx->flags);
	init_stack(ctx->a, 'a');
	init_stack(ctx->b, 'b');
	return (init_and_fill_stack(ctx->a, argc, argv, ctx->in));
}

/**
 * @brief Calculates disorder, selects strategy, and executes sorting.
 * @param a Stack A, b Stack B, f Sorting flags, in Input context.
 */

void	run_sorting(t_stack *a, t_stack *b, t_flags *f, t_input *in)
{
	double	disorder;

	disorder = compute_disorder(in->arr, in->size);
	free(in->arr);
	op_counter(-1);
	sort_stack(a, b, f, disorder);
	cleanup(a, b);
}
