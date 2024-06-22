/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_position.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 01:31:56 by ssghioua          #+#    #+#             */
/*   Updated: 2024/06/18 01:31:57 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/push_swap.h"

void	find_target_position_b(t_stack *stack_a, t_stack *stack_b)
{
	t_stack	*current_a;
	t_stack	*target;
	long	nearest_value;

	while (stack_b)
	{
		nearest_value = LONG_MAX;
		current_a = stack_a;
		while (current_a)
		{
			if (current_a->value > stack_b->value
				&& current_a->value < nearest_value)
			{
				nearest_value = current_a->value;
				target = current_a;
			}
			current_a = current_a->next;
		}
		if (nearest_value == LONG_MAX)
			stack_b->target = get_small_node(stack_a);
		else
			stack_b->target = target;
		stack_b = stack_b->next;
	}
}

void	find_target_position_a(t_stack *stack_a, t_stack *stack_b)
{
	t_stack	*current_b;
	t_stack	*target;
	long	nearest_value;

	while (stack_a)
	{
		nearest_value = LONG_MIN;
		current_b = stack_b;
		while (current_b)
		{
			if (current_b->value < stack_a->value
				&& current_b->value > nearest_value)
			{
				nearest_value = current_b->value;
				target = current_b;
			}
			current_b = current_b->next;
		}
		if (nearest_value == LONG_MIN)
			stack_a->target = get_big_node(stack_b);
		else
			stack_a->target = target;
		stack_a = stack_a->next;
	}
}
