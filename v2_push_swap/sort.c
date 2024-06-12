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
	while (len_a-- > 3 && !is_sorted(*stack_a))
	{
		update_nodes_a(*stack_a, *stack_b);
		// move_a_to_b(stack_a, stack_b);
	}
	
}

void	update_nodes_a(t_stack *stack_a, t_stack *stack_b)
{
	update_index(stack_a);
	update_index(stack_b);
	init_target_a(stack_a, stack_b);
	// get_operation_cost(stack_a, stack_b);
	// set_best_move(stack_a);
}

void	update_index(t_stack *stack)
{
	int	i;
	int	half;

	i = 0;
	if (!stack)
		return ;
	half = get_stack_len(stack) / 2;
	while (stack)
	{
		stack -> index = i;
		if (i > half)
			stack -> above_half = true;
		else
			stack -> above_half = false;
		stack = stack -> next;
		i++;
	}
}

void	init_target_a(t_stack *stack_a, t_stack *stack_b)
{
	t_stack	*current_b;
	t_stack	*target_node;
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
				target_node = current_b;
			}
			current_b = current_b -> next;
		}
		if (nearest_value == LONG_MIN)
			stack_a -> target_node = get_big_node(stack_b);
		else
			stack_a -> target_node = target_node;
		stack_a = stack_a -> next;
	}
}

void	get_operations_cost(t_stack *stack_a, t_stack *stack_b)
{
	int	len_a;
	int	len_b;

	len_a = get_stack_len(stack_a);
	len_b = get_stack_len(stack_b);
	while (stack_a)
	{
		stack_a -> operations_cost = (stack_a -> index);
		if (!(stack_a -> above_half))
			stack_a -> operations_cost = len_a - (stack_a -> index);
		if (!(stack_a -> target_node -> above_half))
			(stack_a -> operations_cost) += (len_b - (stack_a -> target_node -> index));
		else
			(stack_a -> operations_cost) += (stack_a -> target_node -> index);
		stack_a = (stack_a -> next);
	}
}
