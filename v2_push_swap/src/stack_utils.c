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
	int	i;

	i = 0;
	while (stack)
	{
		i++;
		stack = stack -> next;
	}
	return (i);
}

t_stack	*get_big_node(t_stack *stack)
{
	t_stack	*big_node;
	int		big_value;

	big_value = INT_MIN;
	big_node = stack;
	while (stack)
	{
		if (stack -> value > big_value)
		{
			big_value = stack -> value;
			big_node = stack;
		}
		stack = stack -> next;
	}
	return (big_node);
}

t_stack	*get_small_node(t_stack *stack)
{
	t_stack	*small_node;
	int		small_val;

	small_val = INT_MAX;
	small_node = stack;
	while (stack)
	{
		if (stack -> value < small_val)
		{
			small_val = stack -> value;
			small_node = stack;
		}	
		stack = stack -> next;
	}
	return (small_node);
}
