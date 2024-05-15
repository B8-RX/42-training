
#include "./include/push_swap.h"

void	sa(t_stack	**stack_a)
{
	t_stack	*first_node;
	t_stack	*second_node;
	
	first_node = *stack_a;
	second_node = (*stack_a) -> next;
	first_node -> prev = second_node;
	first_node -> next = second_node -> next;
	second_node -> next = first_node;
	second_node -> prev = NULL;
	*stack_a = second_node;
}

void	sb(t_stack	**stack_b)
{
	t_stack	*first_node;
	t_stack	*second_node;
	
	first_node = *stack_b;
	second_node = (*stack_b) -> next;
	first_node -> prev = second_node;
	first_node -> next = second_node -> next;
	second_node -> next = first_node;
	second_node -> prev = NULL;
	*stack_b = second_node;
}

void	ss(t_stack **stack_a, t_stack **stack_b)
{
	sa(stack_a);
	sb(stack_b);
}

void	ra(t_stack **stack_a)
{
	t_stack	*first_node;
	t_stack	*last_node;

	first_node = *stack_a;
	last_node = get_last_node(*stack_a);
	last_node -> next = first_node -> next;
	last_node -> prev -> next = first_node;
	first_node -> prev = last_node -> prev;
	first_node -> next = NULL;
	last_node -> prev = NULL;
	*stack_a = last_node;
}

t_stack	*get_last_node(t_stack *stack)
{
	while (stack -> next)
		stack = stack -> next;
	return (stack);
}
