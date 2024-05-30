#include "./include/push_swap.h"

void	tests_functions(void)
{

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
				head = new_node;
			else
				(*stack_test) -> next = new_node;
			*stack_test = new_node;
		}
		*stack_test = head;
	}


	void	test_function_big_value(t_stack *stack_test, int biggest_value)
	{
		int i;
		
		if (!stack_test)
			return ; 
		i = get_big_value(stack_test);
		if (biggest_value)
			printf("When call get_big_value(stack) it should return [%d]\n", biggest_value);
		printf("THE RETURNED VALUE OF GET_BIG_VALUE IS : [%d]\n", i);
		printf("\n");
		free_stack_test(stack_test);
	}

	
	void	test_function_get_last_node(t_stack *stack_test, int last_node_value)
	{
		t_stack *last_node;

		if (!stack_test)
			return ;
		last_node = get_last_node(stack_test);
		if (last_node_value)
			printf("When call get_last_node(stack) it should return the last node which have [%d] as value\n", last_node_value);
		printf("THE RETURNED NODE OF GET_LAST_NODE HAVE VALUE : [%d]\n", last_node -> value);
		printf("\n");
		free_stack_test(stack_test);
	}


	void	test_function_get_stack_len(t_stack *stack, int stack_len)
	{
		int	result;

		if (!stack)
			return ;
		result = get_stack_len(stack);
		printf("When call get_stack_len(stack) it should return [%d]\n", stack_len);
		printf("THE RETURNED VALUE OF GET_STACK_LEN() IS : [%d]\n", result);
		printf("\n");
	}

	printf("\n");
	t_stack	*stack_test;
	int		nodes_quantity;

	stack_test = NULL;
	nodes_quantity = 37;
	init_stack_test(&stack_test, nodes_quantity);
	test_function_big_value(stack_test, nodes_quantity);
	nodes_quantity = 15;
	init_stack_test(&stack_test, nodes_quantity);
	test_function_get_last_node(stack_test, nodes_quantity);
	nodes_quantity = 21;
	init_stack_test(&stack_test, nodes_quantity);
	test_function_get_stack_len(stack_test, nodes_quantity);
}
