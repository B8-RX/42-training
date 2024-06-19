/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 23:16:09 by ssghioua          #+#    #+#             */
/*   Updated: 2024/06/18 23:16:11 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/push_swap.h"

void	rra(t_stack **stack_a, int print)
{
	t_stack	*last_node;
	t_stack	*first_node;

	if (!*stack_a)
		return ;
	if (print)
		ft_printf("rra\n");
	first_node = *stack_a;
	last_node = get_last_node(*stack_a);
	if (get_stack_len(*stack_a) > 2)
		last_node -> prev -> next = NULL;
	else
		first_node -> next = NULL;
	first_node -> prev = last_node;
	last_node -> prev = NULL;
	last_node -> next = first_node;
	*stack_a = last_node;
	update_index(*stack_a);
}

void	rrb(t_stack **stack_b, int print)
{
	t_stack	*last_node;
	t_stack	*first_node;

	if (!*stack_b)
		return ;
	if (print)
		ft_printf("rrb\n");
	first_node = *stack_b;
	last_node = get_last_node(*stack_b);
	if (get_stack_len(*stack_b) > 2)
		last_node -> prev -> next = NULL;
	else
		first_node -> next = NULL;
	first_node -> prev = last_node;
	last_node -> prev = NULL;
	last_node -> next = first_node;
	*stack_b = last_node;
	update_index(*stack_b);
}

void	rrr(t_stack	**stack_a, t_stack **stack_b, int print)
{
	if (!*stack_a || !*stack_b)
		return ;
	if (print)
		ft_printf("rrr\n");
	rra(stack_a, 0);
	rrb(stack_b, 0);
}
