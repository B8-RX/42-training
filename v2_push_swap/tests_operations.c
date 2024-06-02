#include "./include/push_swap.h"

void		tests_operations_functions(void)
{
	t_stack	*stack_test;
	int		node_quantity;

	stack_test = NULL;
	node_quantity = 2;

	void	test_function_sa_sb(char function_name)
	{
		printf("TEST FUNCTION SA() SB()\n");
		int	first_node_value;
		int	second_node_value;

		init_stack_test(&stack_test, node_quantity);
		
		first_node_value = stack_test -> value;
		second_node_value = stack_test -> next -> value;
		
// test first node
		printf("When call the function sa() or sb() with 'stack_len' as argument, the member 'value' of the FIRST NODE SHOULD BE EQUAL TO [%d]\n", second_node_value);
		if (function_name == 'a')
			sa(&stack_test, 1);
		else
			sb(&stack_test, 1);
		printf("FIRST NODE VALUE: [%d]\n\n", stack_test -> value);
// test second node
		printf("When call the function sa() or sb() with 'stack_len' as argument, the member 'value' of the SECOND SHOULD BE EQUAL TO [%d]\n", first_node_value);
		printf("SECOND NODE VALUE: [%d]\n\n", stack_test -> next -> value);
		printf("//////////////\n\n");
		free_stack_test(stack_test);
	}

	void	test_function_ss()
	{
		printf("TEST FUNCTION SS()\n");
		test_function_sa_sb('a');
		test_function_sa_sb('b');
	}

	void	test_function_ra_rb(char function_name)
	{
		printf("TEST FUNCTION RA() RB()\n");
		int	first_node_value;

		node_quantity = 5;
		init_stack_test(&stack_test, node_quantity);
		first_node_value = stack_test -> value;
// test first node 
		printf("When call the function ra() or rb() whith 'stack_len' as argument the value of the FIRST NODE SHOULD NOT BE EQUAL TO [%d]\n", first_node_value);
		if (function_name == 'a')
			ra(&stack_test, 1);
		else
			rb(&stack_test, 1);
		printf("FIRST NODE VALUE: [%d]\n\n", stack_test -> value);
	
// test last node
		printf("When call the function ra() or rb() whith 'stack_len' as argument the value of the LAST NODE SHOULD BE EQUAL TO [%d]\n", first_node_value);
		printf("LAST NODE VALUE: [%d]\n\n", get_last_node(stack_test) -> value);
		printf("////////////////////\n\n");
		free_stack_test(stack_test);

	}

	test_function_sa_sb('a');
	test_function_sa_sb('b');
	test_function_ss();
	test_function_ra_rb('b');
}


