/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 01:26:47 by ssghioua          #+#    #+#             */
/*   Updated: 2024/06/18 01:30:03 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/push_swap.h"

void	count_move_steps_a(t_stack *stack_a, t_stack *stack_b)
{
	int	len_a;
	int	len_b;

	len_b = get_stack_len(stack_b);
	len_a = get_stack_len(stack_a);
	while (stack_a)
	{
		if (stack_a->index == 1)
			stack_a->operation_steps = 0;
		else if (stack_a->in_upper_half)
			stack_a->operation_steps = stack_a->index;
		else
			stack_a->operation_steps = len_a - stack_a->index + 1;
		if (stack_a->target->index == 1)
			stack_a->operation_steps += 0;
		else if (stack_a->target->in_upper_half)
			stack_a->operation_steps += stack_a->target->index;
		else
			stack_a->operation_steps += len_b - stack_a->target->index + 1;
		stack_a = stack_a->next;
	}
}

void	count_move_steps_b(t_stack *stack_a, t_stack *stack_b)
{
	int	len_a;
	int	len_b;

	len_a = get_stack_len(stack_a);
	len_b = get_stack_len(stack_b);
	while (stack_b)
	{
		if (stack_b->index == 1)
			stack_b->operation_steps = 0;
		else if (stack_b->in_upper_half)
			stack_b->operation_steps = stack_b->index;
		else
			stack_b->operation_steps = len_b - stack_b->index;
		if (stack_b->target->index == 1)
			stack_b->operation_steps += 0;
		else if (stack_b->target->in_upper_half)
			stack_b->operation_steps += stack_b->target->index;
		else
			stack_b->operation_steps += len_a - stack_b->target->index;
		stack_b = stack_b->next;
	}
}
