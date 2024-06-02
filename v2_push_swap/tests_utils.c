
#include "./include/push_swap.h"	

void	free_stack_test(t_stack *stack_test)
{
	t_stack	*temp;

	if (!stack_test)
		return ;
	while (stack_test)
	{
		temp = stack_test -> next;
		free(stack_test);
		stack_test = NULL;
		stack_test = temp;
	}
}

void	init_stack_test(t_stack **stack_test, int nodes)
{
	t_stack	*new_node;
	t_stack	*head;
	int		i;

	i = 0;
	head = NULL;
	while (++i <= nodes)
	{
		new_node = malloc (sizeof(t_stack));
		if (!new_node)
		{
			if (head)
			{
				free_stack_test(head);
				*stack_test = NULL;
			}
			return ;
		}
		new_node -> value = i;
		new_node -> next = NULL;
		if (!head)
		{
			new_node -> prev = NULL;
			head = new_node;
		}
		else
		{
			new_node -> prev = *stack_test;
			(*stack_test) -> next = new_node;
		}
		*stack_test = new_node;
	}
	*stack_test = head;
}


