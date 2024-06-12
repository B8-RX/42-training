#include "../include/push_swap.h"
#include <time.h>

void		tests_operations_functions(void)
{
	t_stack	*stack_test;
	int		node_quantity;

	stack_test = NULL;
	node_quantity = 55;
	srand(time(NULL));

	void	test_function_sa_sb(char function_name)
	{
		printf("##################################################################\n");
		printf("##################################################################\n");
		if (function_name == 'a')
			printf("\t\t\t\t/////START TEST FUNCTION SA()/////\n\n");
		else
			printf("\t\t\t\t/////START TEST FUNCTION SB()/////\n\n");
		t_stack	*first_node;
		t_stack	*second_node;

		init_stack_test(&stack_test, node_quantity);
		
		first_node = stack_test;
		second_node = stack_test -> next;
		if (function_name == 'a')
			sa(&stack_test, 0);
		else
			sb(&stack_test, 0);
		
		printf("When call the function sa(stack_test) or sb(stack_test) the member 'value' of the \nFIRST NODE SHOULD BE EQUAL TO [%d]\n", second_node -> value);
		printf("-------------->\n");
		printf("\tRESULT FIRST NODE VALUE: [%d]\n\n", stack_test -> value);
		
		printf("When call the function sa(stack_test) or sb(stack_test) the member 'value' of the \nSECOND NODE SHOULD BE EQUAL TO [%d]\n", first_node -> value);
		printf("-------------->\n");
		printf("\tRESULT SECOND NODE VALUE: [%d]\n\n", stack_test -> next -> value);
		printf("\\\\\\\\\\END\\\\\\\\\\\n\n");
		free_stack_test(stack_test);
	}

	void	test_function_ss()
	{
		printf("##################################################################\n");
		printf("##################################################################\n");
		printf("\t\t\t\t/////START TEST FUNCTION SS()/////\n\n");
		t_stack	*stack_a;
		t_stack	*stack_b;
		t_stack	*first_node_a;
		t_stack	*first_node_b;

		node_quantity = 45;
		stack_a = NULL;
		stack_b = NULL;
		init_stack_test(&stack_a, node_quantity);
		init_stack_test(&stack_b, node_quantity);
		first_node_a = stack_a;
		first_node_b = stack_b;
		printf("STARTING FIRST NODES VALUES:\n\tVALUE NODE STACK_A: [%d]\n\tVALUE NODE STACK_B: [%d]\n", first_node_a -> value, first_node_b -> value);
		ss(&stack_a, &stack_b, 0);
		printf("When call function ss(stack_a, stack_b) the \nFIRST NODE VALUE OF STACK_A SHOULD NOT BE: [%d]\n", first_node_a -> value);
		printf("-------------->\n");
		printf("\tRESULT FIRST NODE STACK_A VALUE: [%d], (OLD FIRST NODE VALUE: [%d])\n\n", stack_a -> value, first_node_a -> value);
	
		printf("When call function ss(stack_a, stack_b) the \nFIRST NODE VALUE OF STACK_B SHOULD NOT BE: [%d]\n", first_node_b -> value);
		printf("-------------->\n");
		printf("\tRESULT FIRST NODE STACK_B VALUE: [%d], (OLD FIRST NODE VALUE: [%d])\n\n", stack_b -> value, first_node_b -> value);
		printf("\\\\\\\\\\END\\\\\\\\\\\n\n");
		free_stack_test(stack_a);
		free_stack_test(stack_b);		
	}

	void	test_function_ra_rb(char function_name)
	{
		printf("##################################################################\n");
		printf("##################################################################\n");
		if (function_name == 'a')
			printf("\t\t\t\t/////START TEST FUNCTION RA()/////\n\n");
		else
			printf("\t\t\t\t/////START TEST FUNCTION RB()/////\n\n");
		t_stack	*first_node;

		node_quantity = 85;
		init_stack_test(&stack_test, node_quantity);
		first_node = stack_test;
		if (function_name == 'a')
			ra(&stack_test, 0);
		else
			rb(&stack_test, 0);
	
		printf("When call the function ra(stack_test) or rb(stack_test) the value of the \nFIRST NODE SHOULD NOT BE EQUAL TO [%d]\n", first_node -> value);
		printf("\tRESULT FIRST NODE VALUE: [%d]\n\n", stack_test -> value);
	
		printf("When call the function ra(stack_test) or rb(stack_test) the value of the  \nLAST NODE SHOULD BE EQUAL TO [%d]\n", first_node -> value);
		printf("-------------->\n");
		printf("\tRESULT LAST NODE VALUE: [%d]\n\n", get_last_node(stack_test) -> value);
		printf("\\\\\\\\\\END\\\\\\\\\\\n\n");
		free_stack_test(stack_test);

	}

	void	test_function_rr()
	{
		printf("##################################################################\n");
		printf("##################################################################\n");
		printf("\t\t\t\t/////START TEST FUNCTION RR()/////\n");
		t_stack	*stack_a;
		t_stack	*stack_b;
		t_stack	*first_node_a;
		t_stack	*last_node_a;
		t_stack	*first_node_b;
		t_stack	*last_node_b;

		stack_a = NULL;
		stack_b = NULL;
		node_quantity = 27;
		init_stack_test(&stack_a, node_quantity);
		node_quantity = 18;
		init_stack_test(&stack_b, node_quantity);
		first_node_a = stack_a;
		first_node_b = stack_b;
		last_node_a = get_last_node(stack_a);
		last_node_b = get_last_node(stack_b);
		printf("STARTING VALUES STACK_A:\n");
		printf("\tFIRST NODE VALUE: [%d]\n", first_node_a -> value);
		printf("\tLAST NODE VALUE: [%d]\n", last_node_a -> value);
		printf("STARTING VALUES STACK_B:\n");
		printf("\tFIRST NODE VALUE: [%d]\n", first_node_b -> value);
		printf("\tLAST NODE VALUE: [%d]\n", last_node_b -> value);
		
		rr(&stack_a, &stack_b, 0);

		printf("When call the function rr(stack_a, stack_b, 0) the \nLAST NODE VALUE OF STACK_A SHOULD BE EQUAL TO: [%d]\n", first_node_a -> value);
		printf("-------------->\n");
		printf("\tRESULT LAST NODE VALUE STACK_A: [%d] (OLD VALUE: [%d])\n\n", get_last_node(stack_a) -> value, last_node_a -> value);

		printf("When call the function rr(stack_a, stack_b, 0) the \nLAST NODE VALUE OF STACK_B SHOULD BE EQUAL TO: [%d]\n", first_node_b -> value);
		printf("-------------->\n");
		printf("\tRESULT LAST NODE VALUE STACK_B: [%d] (OLD VALUE: [%d])\n\n", get_last_node(stack_b) -> value, last_node_b -> value);
		printf("\\\\\\\\\\END\\\\\\\\\\\n\n");
		free_stack_test(stack_a);
		free_stack_test(stack_b);
	}

	void	test_function_rra_rrb(char function_name)
	{
		printf("##################################################################\n");
		printf("##################################################################\n");
		if (function_name == 'a')
			printf("\t\t\t\t/////START TEST FUNCTION RRA()/////\n\n");
		else
			printf("\t\t\t\t/////START TEST FUNCTION RRB()/////\n\n");
		t_stack	*first_node;
		t_stack	*last_node;

		node_quantity = 200;
		init_stack_test(&stack_test, node_quantity);
		first_node = stack_test;
		last_node = get_last_node(stack_test);
		printf("STARTING NODE VALUES:\n");
		printf("\tFIRST NODE VALUE: [%d]\n", first_node -> value);
		printf("\tLAST NODE VALUE: [%d]\n", last_node -> value);
		if (function_name == 'a')
			rra(&stack_test, 0);
		else
			rrb(&stack_test, 0);
		
		printf("When call the function rra(stack_test) or rrb(stack_test)the \nFIRST NODE VALUE SHOULD BE EQUAL TO: [%d]\n", last_node -> value);
		printf("-------------->\n");
		printf("\tRESULT FIRST NODE VALUE: [%d] (OLD VALUE: [%d])\n\n", stack_test -> value, first_node -> value);
		printf("\\\\\\\\\\END\\\\\\\\\\\n\n");
		free_stack_test(stack_test);
	}

	void	test_function_rrr()
	{
		printf("##################################################################\n");
		printf("##################################################################\n");
		printf("\t\t\t\t/////START TEST FUNCTION RRR()/////\n\n");
		t_stack	*stack_a;
		t_stack	*stack_b;
		t_stack	*first_node_a;
		t_stack	*last_node_a;
		t_stack	*first_node_b;
		t_stack	*last_node_b;

		stack_a = NULL;
		stack_b = NULL;
		node_quantity = 5;
		init_stack_test(&stack_a, node_quantity);
		node_quantity = 360;
		init_stack_test(&stack_b, node_quantity);
		first_node_a = stack_a;
		first_node_b = stack_b;
		last_node_a = get_last_node(stack_a);
		last_node_b = get_last_node(stack_b);
		printf("STARTING VALUES STACK_A:\n");
		printf("\tFIRST NODE VALUE: [%d]\n", first_node_a -> value);
		printf("\tLAST NODE VALUE: [%d]\n", last_node_a -> value);
		printf("STARTING VALUES STACK_B:\n");
		printf("\tFIRST NODE VALUE: [%d]\n", first_node_b -> value);
		printf("\tLAST NODE VALUE: [%d]\n", last_node_b -> value);
		
		rrr(&stack_a, &stack_b, 0);
		
		printf("When call the function rrr(stack_a, stack_b, 0) the \nFIRST NODE VALUE OF STACK_A SHOULD BE EQUAL TO: [%d]\n", last_node_a -> value);
		printf("-------------->\n");
		printf("\tRESULT FIRST NODE VALUE STACK_A: [%d] (OLD VALUE: [%d])\n\n", stack_a -> value, first_node_a -> value);
		
		printf("When call the function rrr(stack_a, stack_b, 0) the \nFIRST NODE VALUE OF STACK_B SHOULD BE EQUAL TO: [%d]\n", last_node_b -> value);
		printf("-------------->\n");
		printf("\tRESULT FIRST NODE VALUE STACK_A: [%d] (OLD VALUE: [%d])\n\n", stack_b -> value, first_node_b -> value);
		printf("\\\\\\\\\\END\\\\\\\\\\\n\n");
		free_stack_test(stack_a);
		free_stack_test(stack_b);
	}

	void	test_function_pa()
	{
		printf("##################################################################\n");
		printf("##################################################################\n");
		printf("\t\t\t\t/////START TEST FUNCTION PA()/////\n\n");
		t_stack	*stack_a;
		t_stack	*stack_b;
		size_t	initial_len_stack_a;
		size_t	initial_len_stack_b;

		stack_a = NULL;
		stack_b = NULL;
		node_quantity = 37;
		init_stack_test(&stack_a, node_quantity);
		node_quantity = 86;
		init_stack_test(&stack_b, node_quantity);
		initial_len_stack_a = get_stack_len(stack_a);
		initial_len_stack_b = get_stack_len(stack_b);
		pa(&stack_b, &stack_a, 0);

		printf("STARTING LENGHTS: \n\tSTACK_A => [%zu]\n\tSTACK_B => [%zu]\n\n", initial_len_stack_a, initial_len_stack_b);
		printf("When call pa(stack_a, stack_b) the \nLEN OF STACK_B SHOULD BE: [%zu]\n", initial_len_stack_b - 1);
		printf("-------------->\n");
		printf("\tRESULT STACK_B LEN: [%d]\n\n", get_stack_len(stack_b));
		printf("When call pa(stack_a, stack_b) the \nLEN OF STACK_A SHOULD BE: [%zu]\n", initial_len_stack_a + 1);
		printf("-------------->\n");
		printf("\tRESULT STACK_A LEN: [%d]\n\n", get_stack_len(stack_a));
		printf("\\\\\\\\\\END\\\\\\\\\\\n\n");
		free_stack_test(stack_a);
		free_stack_test(stack_b);
	}

	void	test_function_pb()
	{
		printf("##################################################################\n");
		printf("##################################################################\n");
		printf("\t\t\t\t/////START TEST FUNCTION PB()/////\n\n");
		t_stack	*stack_a;
		t_stack	*stack_b;
		size_t	initial_len_stack_a;
		size_t	initial_len_stack_b;
		int		initial_first_node_stack_a_value;
		int		initial_first_node_stack_b_value;
		
		stack_a = NULL;
		stack_b = NULL;
		init_stack_test(&stack_a, random_number(3, 500));
		init_stack_test(&stack_b, random_number(3, 500));
		initial_first_node_stack_a_value = stack_a -> value;
		initial_first_node_stack_b_value = stack_b -> value;
		initial_len_stack_a = get_stack_len(stack_a);
		initial_len_stack_b = get_stack_len(stack_b);
		pb(&stack_a, &stack_b, 0);

		 printf("STARTING LENGHTS AND VALUES: \n\tSTACK_A: LENGHT = [%zu] FIRST NODE VALUE = [%d]\n\tSTACK_B: LENGHT = [%zu] FIRST NODE VALUE = [%d]\n\n", initial_len_stack_a, initial_first_node_stack_a_value, initial_len_stack_b, initial_first_node_stack_b_value);
		printf("When call pb(stack_a, stack_b) the \nLENGHT OF STACK_B SHOULD BE: [%zu]\nVALUE OF FIRST NODE STACK_b SHOULD NOT BE [%d]\n", initial_len_stack_b + 1, initial_first_node_stack_b_value);
		printf("-------------->\n");
		printf("\tRESULT STACK_B: \nLENGHT: [%d]\nFIRST NODE VALUE [%d]\n\n", get_stack_len(stack_b), stack_b -> value);
		printf("When call pb(stack_a, stack_b) the \nLENGHT OF STACK_A SHOULD BE: [%zu]\nVALUE OF FIRST NODE STACK_A SHOULD NOT BE [%d]\n", initial_len_stack_a - 1, initial_first_node_stack_a_value);
		printf("-------------->\n");
		printf("\t\tRESULT STACK_A: \nLENGHT: [%d]\nFIRST NODE VALUE [%d]\n\n", get_stack_len(stack_a), stack_a -> value);
		printf("\\\\\\\\\\END\\\\\\\\\\\n\n");
		free_stack_test(stack_a);
		free_stack_test(stack_b);
	}
	test_function_sa_sb('a');
	test_function_sa_sb('b');
	test_function_ss(); // todo: refactore this like rr() and rrr()
	test_function_ra_rb('a');
	test_function_ra_rb('b');
	test_function_rr();
	test_function_rra_rrb('a');
	test_function_rra_rrb('b');
	test_function_rrr();
	test_function_pa();
	test_function_pb();
}


