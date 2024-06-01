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


	void	test_function_big_value()
	{
		printf("TEST GET_BIG_VALUE()\n");
		int result;
		
		nodes_quantity = 37;
		init_stack_test(&stack_test, nodes_quantity);
		if (!stack_test)
			return ; 
		result = get_big_value(stack_test);
		printf("When call get_big_value() it should return [%d]\n", nodes_quantity);
		printf("THE RETURNED VALUE OF GET_BIG_VALUE() IS : [%d]\n", result);
		printf("\n");
		free_stack_test(stack_test);
	}

	
	void	test_function_get_last_node()
	{
		printf("TEST GET_LAST_NODE()\n");
		t_stack *last_node;
		int		last_node_value;

		nodes_quantity = 15;
		last_node_value = nodes_quantity;
		init_stack_test(&stack_test, nodes_quantity);
		if (!stack_test)
			return ;
		last_node = get_last_node(stack_test);
		printf("When call get_last_node() it should return the last node which have [%d] as value\n", last_node_value);
		printf("THE RETURNED NODE OF GET_LAST_NODE() HAVE VALUE : [%d]\n", last_node -> value);
		printf("\n");
		free_stack_test(stack_test);
	}


	void	test_function_get_stack_len()
	{
		printf("TEST GET_STACK_LEN()\n");
		int	result;
		int	stack_len;
		
		nodes_quantity = 21;
		stack_len = nodes_quantity;
		init_stack_test(&stack_test, nodes_quantity);
		if (!stack_test)
			return ;
		result = get_stack_len(stack_test);
		printf("When call get_stack_len() it should return [%d]\n", stack_len);
		printf("THE RETURNED VALUE OF GET_STACK_LEN() IS : [%d]\n", result);
		printf("\n");
		free_stack_test(stack_test);
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

	void	test_function_is_duplicate()
	{
		int	val_in_stack;
		int	val_not_in_stack;

		val_in_stack = 5;
		val_not_in_stack = 10;
		printf("TEST IS_DUPLICATE()\n");
		nodes_quantity = 5;
		init_stack_test(&stack_test, nodes_quantity);
		printf("When call is_duplicate() with [%d] as argument it should return [1]\n", val_in_stack);
		printf("RETURNED VALUE OF IS_DUPLICATE() : [%d]\n", is_duplicate(stack_test, val_in_stack));
		printf("\n");
		printf("When call is_duplicate() with [%d] as argument it should return [0]\n", val_not_in_stack);
		printf("RETURNED VALUE OF IS_DUPLICATE() : [%d]\n", is_duplicate(stack_test, val_not_in_stack));
		printf("\n");
		free_stack_test(stack_test);
	}

	void	test_function_append_node()
	{
		printf("TEST APPEND_NODE()\n");
		int		node_value;
		t_stack	*tail;

		node_value = 99;
		nodes_quantity = 5;
		init_stack_test(&stack_test, nodes_quantity);
		printf("When call append_node(stack , %d) the value of the last node should be [%d]\n", node_value, node_value);
		append_node(&stack_test, node_value);
		tail = stack_test;
		while (tail -> next)
			tail = tail -> next;
		printf("RETURNED LAST NODE VALUE : [%d]\n", tail -> value);
		printf("\n");
		free_stack_test(stack_test);
	}

	void	test_function_free_on_error()
	{
		char	**arr;
		char	*str1;
		char	*str2;


		str1 = "123";
		str2 = "456";
		arr = malloc (sizeof(char *) * 3);
		if (!arr)
			return ;
		arr[0] = malloc (sizeof(char) * ft_strlen(str1) + 1);
		if (!arr[0])
			return ;
		arr[1] = malloc (sizeof(char) * ft_strlen(str2) + 1);
		if (!arr[1])
			return ;
	
		ft_strlcpy(arr[0], str1, ft_strlen(str1) + 1);
		ft_strlcpy(arr[1], str2, ft_strlen(str1) + 1);
		arr[2] = NULL;
		nodes_quantity = 3;
		init_stack_test(&stack_test, nodes_quantity);
		printf("When call free_on_error() with stack_test and arr as arguments they should be equal to NULL after the call\n");
		free_on_error(&stack_test, &arr);
		printf("RETURNED VALUE:\nARR IS NULL ? [%s]\nSTACK_LEN IS NULL ? [%s]\n", arr == NULL ? "true" : "false" , stack_test == NULL ? "true" : "false");
		printf("\n");
	}


	printf("/////////////////////////\n");
	test_function_big_value();
	
	printf("/////////////////////////\n");
	test_function_get_last_node();
	
	printf("/////////////////////////\n");
	test_function_get_stack_len();
	
	printf("/////////////////////////\n");
	test_function_is_numeric();
	
	printf("/////////////////////////\n");
	test_function_is_duplicate();
	
	printf("/////////////////////////\n");
	test_function_append_node();
	
	printf("/////////////////////////\n");
	test_function_free_on_error();
}
