/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   untils_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 14:20:10 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/17 14:20:17 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/**
 * Initializes program structures and validates input.
 * Returns 1 on success, 0 on failure.
 */
int	init_environment(int argc, char **argv, t_context *ctx)
{
	parse_flags(argc, argv, ctx->flags);
	init_stack(ctx->a, 'a');
	init_stack(ctx->b, 'b');
	return (init_and_fill_stack(ctx->a, argc, argv, ctx->in));
}

void	run_sorting(t_stack *a, t_stack *b, t_flags *f, t_input *in)
{
	double	disorder;

	disorder = compute_disorder(in->arr, in->size);
	free(in->arr);
	normalize_index(a);
	op_counter(-1);
	sort_stack(a, b, f, disorder);
	cleanup(a, b);
}
