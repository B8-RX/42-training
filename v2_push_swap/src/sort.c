/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:57:15 by ssghioua          #+#    #+#             */
/*   Updated: 2024/06/16 20:57:16 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/push_swap.h"

void	sort_three(t_stack	**stack_a)
{
	t_stack	*big_node;

	big_node = get_big_node(*stack_a);
	if (*stack_a == big_node)
		ra(stack_a, 1);
	else if ((*stack_a) -> next == big_node)
		rra(stack_a, 1);
	if ((*stack_a) -> value > (*stack_a) -> next -> value)
		sa(stack_a, 1); 
}

void	sort_big(t_stack **stack_a, t_stack **stack_b)
{
	int	len_a;

	len_a = get_stack_len(*stack_a);
	if (len_a-- > 3 && !is_sorted(*stack_a))
		pb(stack_a, stack_b, 1);
	if (len_a-- > 3 && !is_sorted(*stack_a))
		pb(stack_a, stack_b, 1);
	ft_print_all_stacks(*stack_a, *stack_b);   // REMOVE BEFORE CORRECTION ALL THE PRINTF
	while (len_a-- > 3 && !is_sorted(*stack_a))
	{
		update_nodes_a(*stack_a, *stack_b);
		ft_print_all_stacks(*stack_a, *stack_b);

		move_to_stack_b(stack_a, stack_b);
	}

	ft_print_all_stacks(*stack_a, *stack_b);
	sort_three(stack_a);
	while (*stack_b)
	{
		update_nodes_b(*stack_a, *stack_b);
		ft_print_all_stacks(*stack_a, *stack_b);
		move_to_stack_a(stack_a, stack_b);		
	}
	small_chunk_at_top(stack_a);	
	ft_print_all_stacks(*stack_a, *stack_b);
}

void	small_chunk_at_top(t_stack **stack_a)
{
	t_stack	*smallest;

	smallest = get_small_node(*stack_a);
	if (smallest -> in_upper_half)
		while (*stack_a != smallest)
			rra(stack_a, 1);
	else
		while (*stack_a != smallest)
			ra(stack_a, 1);
}

void	update_nodes_a(t_stack *stack_a, t_stack *stack_b)
{
	update_index(stack_a);
	update_index(stack_b);
	find_target_position_a(stack_a, stack_b);
	count_move_steps(stack_a, stack_b);
	set_best_move(stack_a);
}

void	update_nodes_b(t_stack *stack_a, t_stack *stack_b)
{
	update_index(stack_a);
	update_index(stack_b);
	find_target_position_b(stack_a, stack_b);
}

void	move_to_stack_a(t_stack **stack_a, t_stack **stack_b)
{
	ready_for_move(stack_a, (*stack_b) -> target, 'a');
	pa(stack_a, stack_b, 1);
}

void	move_to_stack_b(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*best_move_node;

	if (!*stack_a)
		return ;
	best_move_node = get_best_move_node(*stack_a);
	if (best_move_node)
	{
		if ((best_move_node -> in_upper_half)
			&& (best_move_node -> target -> in_upper_half))
			set_up_rr(stack_a, stack_b, best_move_node);
		else if (!(best_move_node -> in_upper_half)
			&& !(best_move_node -> target -> in_upper_half))
			set_up_rrr(stack_a, stack_b, best_move_node);
		ready_for_move(stack_a, best_move_node, 'a');
		ready_for_move(stack_b, best_move_node, 'b');
		pb(stack_a, stack_b, 1);
	}
}

void	ready_for_move(t_stack **stack, t_stack *candidate, char stack_name)
{
	while (*stack != candidate && *stack != candidate -> target)
	{
		if (stack_name == 'a')
		{
			if ((*stack) -> in_upper_half)
				rra(stack, 1);
			else
				ra(stack, 1);
		}
		else if (stack_name == 'b')
		{
			if ((*stack) -> in_upper_half)
				rrb(stack, 1);
			else
				rb(stack, 1);
		}
	}
}

void	set_up_rr(t_stack **stack_a, t_stack **stack_b, t_stack *best_move_node)
{
	while (*stack_a != best_move_node && *stack_b != best_move_node -> target)
		rr(stack_a, stack_b, 1);
}

void	set_up_rrr(t_stack **stack_a, t_stack **stack_b, t_stack *best_move_node)
{
	while (*stack_a != best_move_node && *stack_b != best_move_node -> target)
		rrr(stack_a, stack_b, 1);
}

t_stack	*get_best_move_node(t_stack *stack)
{
	if (!stack)
		return (NULL);
	while (stack)
	{
		if (stack -> is_best_move)
			return (stack);
		stack = stack -> next;
	}
	return (NULL);
}

void	update_index(t_stack *stack)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = get_stack_len(stack);
	if (!stack)
		return ;
	while (stack)
	{
		stack -> index = i;
		if (i < len / 2)
			stack -> in_upper_half = true;
		else
			stack -> in_upper_half = false;
		stack = stack -> next;
		i++;
	}
}

void	set_best_move(t_stack *stack_a)
{
	t_stack	*best_move_node;
	long	current_best_move;

	current_best_move = LONG_MAX;
	if (!stack_a)
		return ;
	best_move_node = stack_a;
	while (stack_a)
	{
		stack_a -> is_best_move = false; 
		if (stack_a -> operation_steps < current_best_move)
		{
			current_best_move = stack_a -> operation_steps;
			best_move_node = stack_a;
		}
		stack_a = stack_a -> next;
	}
	best_move_node -> is_best_move = true;
}

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
			if (current_a -> value > stack_b -> value && current_a -> value < nearest_value)
			{
				nearest_value = current_a -> value;
				target = current_a;
			}
			current_a = current_a -> next;
		}
		if (nearest_value == LONG_MAX)
			stack_b -> target = get_small_node(stack_a);
		else
			stack_b -> target = target;
		stack_b = stack_b -> next;
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
			if (current_b -> value < stack_a -> value && current_b -> value > nearest_value)
			{
				nearest_value = current_b -> value;
				target = current_b;
			}
			current_b = current_b -> next;
		}
		if (nearest_value == LONG_MIN)
			stack_a -> target = get_big_node(stack_b);
		else
			stack_a -> target = target;
		stack_a = stack_a -> next;
	}
}

void	count_move_steps(t_stack *stack_a, t_stack *stack_b)
{
	int	len_a;
	int	len_b;

	len_a = get_stack_len(stack_a);
	len_b = get_stack_len(stack_b);
	while (stack_a)
	{
		stack_a -> operation_steps = (stack_a -> index);
		if (!(stack_a -> in_upper_half))
			stack_a -> operation_steps = len_a - (stack_a -> index);
		if (!(stack_a -> target -> in_upper_half))
			(stack_a -> operation_steps) += (len_b - (stack_a -> target -> index));
		else
			(stack_a -> operation_steps) += (stack_a -> target -> index);
		stack_a = (stack_a -> next);
	}
}
