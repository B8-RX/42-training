
#include "./include/push_swap.h"
#include <time.h>

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

int random_number(int min_num, int max_num)
{
	int result = 0;
	int	floor_num = 0;
	int	ceil_num = 0;

	if (min_num < max_num)
	{
		floor_num = min_num;
		ceil_num = max_num + 1; // include max_num in output
	} else {
		floor_num = max_num + 1; // include max_num in output
		ceil_num = min_num;
	}
	result = (rand() % (ceil_num - floor_num)) + floor_num;
	return result;
}

void	init_stack_test(t_stack **stack_test, int nodes)
{
	t_stack	*new_node;
	t_stack	*head;
	int		i;
	int		value;

	i = 0;
	head = NULL;
	value = random_number(0, 500);
	while (++i <= nodes)
	{
		new_node = malloc (sizeof(t_stack));
		if (!new_node)
		{
			if (head)
			{
				free_stack_test(head);
				head = NULL;
				*stack_test = NULL;
			}
			return ;
		}
		while (head && is_duplicate(head, value))
			value = random_number(0, 500);
		new_node -> value = value;
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
