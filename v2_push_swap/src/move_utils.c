/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 01:35:45 by ssghioua          #+#    #+#             */
/*   Updated: 2024/06/18 01:35:47 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/push_swap.h"

void	set_best_move(t_stack *stack_a)
{
	t_stack	*best_move_node;
	long	current_best_move;

	current_best_move = LONG_MAX;
	if (!stack_a)
		return ;
	best_move_node = stack_a;
	while (stack_a)
	{
		if (stack_a->operation_steps < current_best_move)
		{
			current_best_move = stack_a->operation_steps;
			best_move_node = stack_a;
		}
		stack_a = stack_a->next;
	}
	best_move_node->is_best_move = true;
}

t_stack	*get_best_move_node(t_stack *stack)
{
	if (!stack)
		return (NULL);
	while (stack)
	{
		if (stack->is_best_move)
			return (stack);
		stack = stack->next;
	}
	return (NULL);
}

void	small_chunk_at_top(t_stack **stack_a)
{
	t_stack	*smallest;

	smallest = get_small_node(*stack_a);
	if (smallest->in_upper_half)
		while (*stack_a != smallest)
			rra(stack_a, 1);
	else
		while (*stack_a != smallest)
			ra(stack_a, 1);
}
