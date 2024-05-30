/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:04:24 by ssghioua          #+#    #+#             */
/*   Updated: 2024/05/16 18:04:26 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./include/push_swap.h"

void	sa(t_stack	**stack_a, int print)
{
	t_stack	*first_node;
	t_stack	*second_node;

	if (print)
		printf("sa\n");
	first_node = *stack_a;
	second_node = (*stack_a) -> next;
	first_node -> prev = second_node;
	first_node -> next = second_node -> next;
	second_node -> next = first_node;
	second_node -> prev = NULL;
	*stack_a = second_node;
}

void	sb(t_stack	**stack_b, int print)
{
	t_stack	*first_node;
	t_stack	*second_node;
	
	if (print)
		printf("sb\n");
	first_node = *stack_b;
	second_node = (*stack_b) -> next;
	first_node -> prev = second_node;
	first_node -> next = second_node -> next;
	second_node -> next = first_node;
	second_node -> prev = NULL;
	*stack_b = second_node;
}

void	ss(t_stack **stack_a, t_stack **stack_b, int print)
{
	if (print)
		printf("ss\n");
	sa(stack_a, 0);
	sb(stack_b, 0);
}

void	ra(t_stack **stack_a, int print)
{
	t_stack	*first_node;
	t_stack	*last_node;

	if (print)
		printf("ra\n");
	first_node = *stack_a;
	last_node = get_last_node(*stack_a);
	last_node -> next = first_node -> next;
	last_node -> prev -> next = first_node;
	first_node -> prev = last_node -> prev;
	first_node -> next = NULL;
	last_node -> prev = NULL;
	*stack_a = last_node;
}

void	rb(t_stack **stack_b, int print)
{
	t_stack	*first_node;
	t_stack	*last_node;

	if (print)
		printf("rb\n");
	first_node = *stack_b;
	last_node = get_last_node(*stack_b);
	last_node -> next = first_node -> next;
	last_node -> prev -> next = first_node;
	first_node -> prev = last_node -> prev;
	first_node -> next = NULL;
	last_node -> prev = NULL;
	*stack_b = last_node;
}
