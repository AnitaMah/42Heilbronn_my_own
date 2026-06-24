/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* main.c                                             :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/06/15 13:48:01 by anmakhov          #+#    #+#             */
/* Updated: 2026/06/17 14:22:43 by anmakhov         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/*
** handle_error - Writes an error message to the standard error output.
**
** Returns 1 to indicate an error status.
*/
static int  handle_error(void)
{
    write(2, "Error\n", 6);
    return (1);
}

/*
** cleanup - Frees memory associated with the stacks.
**
** @a: Pointer to stack A.
** @b: Pointer to stack B.
*/
void    cleanup(t_stack *a, t_stack *b)
{
    free_stack(a);
    free_stack(b);
}

/*
** init_and_fill_stack - Parses arguments, checks for duplicates, and 
** initializes stack A.
**
** @a: Pointer to the stack to be filled.
** @argc: Argument count.
** @argv: Argument vector.
** @in: Pointer to input structure containing size and array data.
**
** Returns 1 on success, 0 on failure.
*/
int init_and_fill_stack(t_stack *a, int argc, char **argv, t_input *in)
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

/*
** main - Entry point of the program.
**
** Initializes the environment, checks if the stack is already sorted, 
** and executes the sorting algorithm.
**
** @argc: Argument count.
** @argv: Argument vector.
**
** Returns 0 on success, 1 on error.
*/
int main(int argc, char **argv)
{
    t_input     in;
    t_flags     flags;
    t_stack     a;
    t_stack     b;
    t_context   ctx;

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