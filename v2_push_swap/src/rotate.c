/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 23:15:10 by ssghioua          #+#    #+#             */
/*   Updated: 2024/06/18 23:15:11 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/push_swap.h"

void	ra(t_stack **stack_a, int print)
{
	t_stack	*first_node;
	t_stack	*last_node;
	t_stack	*second_node;

	if (!*stack_a)
		return ;
	if (print)
		ft_printf("ra\n");
	first_node = *stack_a;
	second_node = first_node -> next;
	last_node = get_last_node(*stack_a);
	last_node -> next = first_node;
	first_node -> prev = last_node;
	first_node -> next = NULL;
	second_node -> prev = NULL;
	*stack_a = second_node;
	update_index(*stack_a);
}

void	rb(t_stack **stack_b, int print)
{
	t_stack	*first_node;
	t_stack	*last_node;
	t_stack	*second_node;

	if (!*stack_b)
		return ;
	if (print)
		ft_printf("rb\n");
	first_node = *stack_b;
	second_node = first_node -> next;
	last_node = get_last_node(*stack_b);
	last_node -> next = first_node;
	first_node -> prev = last_node;
	second_node -> prev = NULL;
	first_node -> next = NULL;
	*stack_b = second_node;
	update_index(*stack_b);
}

void	rr(t_stack **stack_a, t_stack **stack_b, int print)
{
	if (!*stack_a || !*stack_b)
		return ;
	if (print)
		ft_printf("rr\n");
	ra(stack_a, 0);
	rb(stack_b, 0);
}
