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
	printf("////////////\n");
	print_values(*stack_b);
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
	get_operation_steps(stack_a, stack_b);
	set_best_move(stack_a);
}

void	update_index(t_stack *stack)
{
	int	i;

	i = 0;
	if (!stack)
		return ;
	while (stack)
	{
		stack -> index = i;
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
		if (stack_a -> operation_steps < current_best_move)
		{
			current_best_move = stack_a -> operation_steps;
			best_move_node = stack_a;
		}
		stack_a = stack_a -> next;
	}
	best_move_node -> is_best_move = true;
	printf("CHEAPEST NODE IS: %d\nTARGET IS: [%d]\n", best_move_node -> value, best_move_node -> target -> value);
}

void	init_target_a(t_stack *stack_a, t_stack *stack_b)
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

void	get_operation_steps(t_stack *stack_a, t_stack *stack_b)
{
	int	len_a;
	int	len_b;

	len_a = get_stack_len(stack_a);
	len_b = get_stack_len(stack_b);
	while (stack_a)
	{
		printf(" VALUE [%d] INDEX [%d]\n", stack_a -> value, stack_a -> index);
		stack_a -> operation_steps = (stack_a -> index);
		if (stack_a -> index > (len_a / 2))
			stack_a -> operation_steps = len_a - (stack_a -> index);
		if (stack_a -> target -> index > (len_b / 2))
			(stack_a -> operation_steps) += (len_b - (stack_a -> target -> index));
		else
			(stack_a -> operation_steps) += (stack_a -> target -> index);
		stack_a = (stack_a -> next);
	}
}


