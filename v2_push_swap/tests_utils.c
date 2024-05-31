#include "./include/push_swap.h"

void	tests_functions(void)
{

	t_stack	*stack_test;
	int		nodes_quantity;

	stack_test = NULL;
	printf("\n");
	

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
		printf("TEST GET_BIG_VALUE()\n");
		int i;
		
		if (!stack_test)
			return ; 
		i = get_big_value(stack_test);
		if (biggest_value)
			printf("When call get_big_value() it should return [%d]\n", biggest_value);
		printf("THE RETURNED VALUE OF GET_BIG_VALUE() IS : [%d]\n", i);
		printf("\n");
	}

	
	void	test_function_get_last_node(t_stack *stack_test, int last_node_value)
	{
		printf("TEST GET_LAST_NODE()\n");
		t_stack *last_node;

		if (!stack_test)
			return ;
		last_node = get_last_node(stack_test);
		if (last_node_value)
			printf("When call get_last_node() it should return the last node which have [%d] as value\n", last_node_value);
		printf("THE RETURNED NODE OF GET_LAST_NODE() HAVE VALUE : [%d]\n", last_node -> value);
		printf("\n");
	}


	void	test_function_get_stack_len(t_stack *stack, int stack_len)
	{
		printf("TEST GET_STACK_LEN()\n");
		int	result;

		if (!stack)
			return ;
		result = get_stack_len(stack);
		printf("When call get_stack_len() it should return [%d]\n", stack_len);
		printf("THE RETURNED VALUE OF GET_STACK_LEN() IS : [%d]\n", result);
		printf("\n");
	}

	void	test_function_is_numeric(void)
	{
		printf("TEST IS_NUMERIC()\n");
		char	*test;

		test = "123";
		printf("When call is_numeric() with [%s] as argument it should return [1]\n", test);
		printf("RETURNED VALUE OF IS_NUMERIC(\"%s\") : [%d]\n", test, is_numeric(test));
		printf("\n");
		test = "1a3";
		printf("When call is_numeric() with [%s] as argument it should return [0]\n", test);
		printf("RETURNED VALUE OF IS_NUMERIC(\"%s\") : [%d]\n", test, is_numeric(test));
		printf("\n");
	}

	void	test_function_is_duplicate(t_stack *stack, int val_in_stack, int val_not_in_stack)
	{
		printf("TEST IS_DUPLICATE()\n");
		printf("When call is_duplicate() with [%d] as argument it should return [1]\n", val_in_stack);
		printf("RETURNED VALUE OF IS_DUPLICATE() : [%d]\n", is_duplicate(stack, val_in_stack));
		printf("\n");
		printf("When call is_duplicate() with [%d] as argument it should return [0]\n", val_not_in_stack);
		printf("RETURNED VALUE OF IS_DUPLICATE() : [%d]\n", is_duplicate(stack, val_not_in_stack));
		printf("\n");
	}

	void	test_function_append_node(t_stack *stack)
	{
		printf("TEST APPEND_NODE()\n");
		int		node_value;
		t_stack	*tail;

		node_value = 99;
		printf("When call append_node(stack , %d) the value of the last node should be [%d]\n", node_value, node_value);
		append_node(&stack, node_value);
		tail = stack;
		while (tail -> next)
			tail = tail -> next;
		printf("RETURNED LAST NODE VALUE : [%d]", tail -> value);
		printf("\n");
	}

	printf("/////////////////////////\n");
	nodes_quantity = 37;
	init_stack_test(&stack_test, nodes_quantity);
	test_function_big_value(stack_test, nodes_quantity);
	free_stack_test(stack_test);
	
	printf("/////////////////////////\n");
	nodes_quantity = 15;
	init_stack_test(&stack_test, nodes_quantity);
	test_function_get_last_node(stack_test, nodes_quantity);
	free_stack_test(stack_test);
	
	printf("/////////////////////////\n");
	nodes_quantity = 21;
	init_stack_test(&stack_test, nodes_quantity);
	test_function_get_stack_len(stack_test, nodes_quantity);
	free_stack_test(stack_test);
	
	printf("/////////////////////////\n");
	test_function_is_numeric();
	
	printf("/////////////////////////\n");
	nodes_quantity = 5;
	init_stack_test(&stack_test, nodes_quantity);
	test_function_is_duplicate(stack_test, nodes_quantity, nodes_quantity + 1);
	free_stack_test(stack_test);
	
	printf("/////////////////////////\n");
	init_stack_test(&stack_test, nodes_quantity);
	test_function_append_node(stack_test);
	free_stack_test(stack_test);
}
