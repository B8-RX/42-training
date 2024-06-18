/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 23:32:30 by ssghioua          #+#    #+#             */
/*   Updated: 2024/06/17 23:32:35 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/push_swap.h"

void	sort_three(t_stack **stack_a)
{
	t_stack	*big_node;

	big_node = get_big_node(*stack_a);
	if (*stack_a == big_node)
		ra(stack_a, 1);
	else if ((*stack_a)->next == big_node)
		rra(stack_a, 1);
	if ((*stack_a)->value > (*stack_a)->next->value)
		sa(stack_a, 1);
}

void	sort_big(t_stack **stack_a)
{
	int		len_a;
	t_stack	*stack_b;

	stack_b = NULL;
	len_a = get_stack_len(*stack_a);
	if (len_a > 3)
	{
		pb(stack_a, &stack_b, 1);
		pb(stack_a, &stack_b, 1);
	}
	while (get_stack_len(*stack_a) > 3)
	{
		update_nodes_a(*stack_a, stack_b);
		move_to_stack_b(stack_a, &stack_b);
	}
	sort_three(stack_a);
	while (stack_b)
	{
		update_nodes_b(*stack_a, stack_b);
		move_to_stack_a(stack_a, &stack_b);
	}
	small_chunk_at_top(stack_a);
	free_stack(stack_b);
}
