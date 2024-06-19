/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 23:18:23 by ssghioua          #+#    #+#             */
/*   Updated: 2024/06/18 23:18:24 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/push_swap.h"

void	pa(t_stack **stack_a, t_stack **stack_b, int print)
{
	t_stack	*node_to_move;

	node_to_move = *stack_b;
	if (!*stack_a || !*stack_b)
		return ;
	if (print)
		ft_printf("pa\n");
	if ((*stack_b)-> next)
	{
		(*stack_b)-> next -> prev = NULL;
		*stack_b = (*stack_b)-> next;
	}
	else
		*stack_b = NULL;
	node_to_move -> next = *stack_a;
	(*stack_a)-> prev = node_to_move;
	*stack_a = node_to_move;
	update_index(*stack_a);
}

void	pb(t_stack **stack_a, t_stack **stack_b, int print)
{
	t_stack	*node_to_move;

	node_to_move = *stack_a;
	if (!*stack_a)
		return ;
	if (print)
		ft_printf("pb\n");
	(*stack_a)-> next -> prev = NULL;
	*stack_a = (*stack_a)-> next;
	node_to_move -> next = *stack_b;
	if (*stack_b)
		(*stack_b)-> prev = node_to_move;
	*stack_b = node_to_move;
	update_index(*stack_b);
}
