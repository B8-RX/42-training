/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 23:17:34 by ssghioua          #+#    #+#             */
/*   Updated: 2024/06/18 23:17:35 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/push_swap.h"

void	sa(t_stack	**stack_a, int print)
{
	t_stack	*first_node;
	t_stack	*second_node;

	if (!*stack_a)
		return ;
	if (print)
		ft_putendl_fd("sa", 1);
	first_node = *stack_a;
	second_node = (*stack_a)-> next;
	second_node -> prev = NULL;
	if (get_stack_len(*stack_a) > 2)
	{
		second_node -> next -> prev = first_node;
		first_node -> next = second_node -> next;
	}
	else
		first_node -> next = NULL;
	first_node -> prev = second_node;
	second_node -> next = first_node;
	*stack_a = second_node;
	update_index(*stack_a);
}

void	sb(t_stack	**stack_b, int print)
{
	t_stack	*first_node;
	t_stack	*second_node;

	if (!*stack_b)
		return ;
	if (print)
		ft_putendl_fd("sb", 1);
	first_node = *stack_b;
	second_node = (*stack_b)-> next;
	second_node -> prev = NULL;
	if (get_stack_len(*stack_b) > 2)
	{
		second_node -> next -> prev = first_node;
		first_node -> next = second_node -> next;
	}
	else
		first_node -> next = NULL;
	first_node -> prev = second_node;
	second_node -> next = first_node;
	*stack_b = second_node;
	update_index(*stack_b);
}

void	ss(t_stack **stack_a, t_stack **stack_b, int print)
{
	if (!*stack_a || !*stack_b)
		return ;
	if (print)
		ft_putendl_fd("ss", 1);
	sa(stack_a, 0);
	sb(stack_b, 0);
}
