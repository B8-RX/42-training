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

	if (!*stack_a)
		return ;
	if (print)
		printf("sa\n");
	first_node = *stack_a;
	second_node = (*stack_a) -> next;
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
		printf("sb\n");
	first_node = *stack_b;
	second_node = (*stack_b) -> next;
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
		printf("ss\n");
	sa(stack_a, 0);
	sb(stack_b, 0);
}

void	ra(t_stack **stack_a, int print)
{
	t_stack	*first_node;
	t_stack	*last_node;
	t_stack	*second_node;

	if (!*stack_a)
		return ;
	if (print)
		printf("ra\n");
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
		printf("rb\n");
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
		printf("rr\n");
	ra(stack_a, 0);
	rb(stack_b, 0);
}

void	rra(t_stack **stack_a, int print)
{
	t_stack	*last_node;
	t_stack	*first_node;

	if (!*stack_a)
		return ;
	if (print)
		printf("rra\n");
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
		printf("rrb\n");
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
		printf("rrr\n");
	rra(stack_a, 0);
	rrb(stack_b, 0);
}

void	pa(t_stack **stack_a, t_stack **stack_b, int print)
{
	t_stack	*node_to_move;

	node_to_move = *stack_b;
	if (!*stack_a || !*stack_b)
		return ;
	if (print)
		printf("pa\n");
	if ((*stack_b) -> next)
	{
		(*stack_b) -> next -> prev = NULL;
		*stack_b = (*stack_b) -> next;
	}
	else
		*stack_b = NULL;
	node_to_move -> next = *stack_a;
	(*stack_a) -> prev = node_to_move;
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
		printf("pb\n");
	(*stack_a) -> next -> prev = NULL;
	*stack_a = (*stack_a) -> next;
	node_to_move -> next = *stack_b;
	if (*stack_b)
		(*stack_b) -> prev = node_to_move;
	*stack_b = node_to_move;
	update_index(*stack_b);
}
