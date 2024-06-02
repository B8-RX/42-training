/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:04:37 by ssghioua          #+#    #+#             */
/*   Updated: 2024/05/16 18:04:38 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/push_swap.h"

t_stack	*get_last_node(t_stack *stack)
{
	while (stack && stack -> next)
		stack = stack -> next;
	return (stack);
}

int	get_stack_len(t_stack *stack)
{
	int i;

	i = 0;
	while (stack)
	{
		i++;
		stack = stack -> next;
	}
	return (i);
}

int	get_big_value(t_stack *stack)
{
	int big_val;

	big_val = INT_MIN;
	while(stack -> next && stack -> value > big_val)
	{
		big_val = stack -> value;
		stack = stack -> next;
	}
	return (stack -> value);
}

void	sort_three(t_stack	**stack_a)
{
	if ((*stack_a) -> value == get_big_value(*stack_a))
		ra(stack_a, 1);
	if ((*stack_a) -> value > (*stack_a) -> next -> value)
		sa(stack_a, 1);
	if (get_last_node(*stack_a) -> value < (*stack_a) -> value)
		rra(stack_a, 1);
}
