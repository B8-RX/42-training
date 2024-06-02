#include "./include/push_swap.h"

void		tests_operations_functions(void)
{
	t_stack	*stack_test;
	int		node_quantity;

	stack_test = NULL;
	node_quantity = 3;

	void	test_function_sa_sb(char function_name)
	{
		if (function_name == 'a')
			printf("TEST FUNCTION SA()\n");
		else
			printf("TEST FUNCTION SB()\n");
		t_stack	*first_node;
		t_stack	*second_node;

		init_stack_test(&stack_test, node_quantity);
		
		first_node = stack_test;
		second_node = stack_test -> next;
		
// test first node
		printf("When call the function sa(stack_test) or sb(stack_test) the member 'value' of the \nFIRST NODE SHOULD BE EQUAL TO [%d]\n", second_node -> value);
		if (function_name == 'a')
			sa(&stack_test, 0);
		else
			sb(&stack_test, 0);
		printf("--------------\n");
		printf("FIRST NODE VALUE: [%d]\n\n", stack_test -> value);
// test second node
		printf("When call the function sa(stack_test) or sb(stack_test) the member 'value' of the \nSECOND NODE SHOULD BE EQUAL TO [%d]\n", first_node -> value);
		printf("--------------\n");
		printf("SECOND NODE VALUE: [%d]\n\n", stack_test -> next -> value);
		printf("/////END//////\n\n");
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
		if (function_name == 'a')
			printf("TEST FUNCTION RA()\n");
		else
			printf("TEST FUNCTION RB()\n");
		t_stack	*first_node;

		node_quantity = 5;
		init_stack_test(&stack_test, node_quantity);
		first_node = stack_test;
// test first node 
		printf("When call the function ra(stack_test) or rb(stack_test) the value of the \nFIRST NODE SHOULD NOT BE EQUAL TO [%d]\n", first_node -> value);
		if (function_name == 'a')
			ra(&stack_test, 0);
		else
			rb(&stack_test, 0);
		printf("FIRST NODE VALUE: [%d]\n\n", stack_test -> value);
	
// test last node
		printf("When call the function ra(stack_test) or rb(stack_test) the value of the  \nLAST NODE SHOULD BE EQUAL TO [%d]\n", first_node -> value);
		printf("--------------\n");
		printf("RESULT LAST NODE VALUE: [%d]\n", get_last_node(stack_test) -> value);
		printf("/////END//////\n\n");
		free_stack_test(stack_test);

	}

	void	test_function_rr()
	{
		printf("TEST FUNCTION RR()\n");
		test_function_ra_rb('a');
		test_function_ra_rb('b');
	}

	void	test_function_rra_rrb(char function_name)
	{
		if (function_name == 'a')
			printf("TEST FUNCTION RRA()\n");
		else
			printf("TEST FUNCTION RRB()\n");
		t_stack	*first_node;
		t_stack	*last_node;

		node_quantity = 20;
		init_stack_test(&stack_test, node_quantity);
		first_node = stack_test;
		last_node = get_last_node(stack_test);
		printf("FIRST NODE VALUE: [%d]\n", first_node -> value);
		if (function_name == 'a')
			rra(&stack_test, 0);
		else
			rrb(&stack_test, 0);
		printf("When call the function rra(stack_test) or rrb(stack_test)the \nFIRST NODE VALUE SHOULD BE EQUAL TO: [%d]\n", last_node -> value);
		// test first node
		printf("--------------\n");
		printf("RESULT FIRST NODE VALUE: [%d]\n", stack_test -> value);
		printf("/////END//////\n\n");
		free_stack_test(stack_test);
	}

	void	test_function_rrr()
	{
		printf("TEST FUNCTION RRR()\n");
		test_function_rra_rrb('a');
		test_function_rra_rrb('b');
	}
	// test_function_sa_sb('a');
	// test_function_sa_sb('b');
	test_function_ss();
	// test_function_ra_rb('a');
	// test_function_ra_rb('b');
	test_function_rr();
	// test_function_rra_rrb('a');
	// test_function_rra_rrb('b');
	test_function_rrr();

}


