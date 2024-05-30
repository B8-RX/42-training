#include "./include/push_swap.h"

void	tests_functions(void)
{
// test function ft_get_big_value(t_stack *stack)
//
	t_stack	*init_stack_test(int num)
	{
		t_stack	*stack_test;
		t_stack *head;
		int		i;

		head = NULL;
		i = 0;
		while (++i <= num)
		{
			t_stack *new_node;

			new_node = malloc (sizeof(t_stack));
			if (!new_node)
				return (NULL);
			new_node -> value = i;
			new_node -> next = NULL;
			if (!head)
				head = new_node;
			else
				stack_test -> next = new_node;
			stack_test = new_node;
		}
		stack_test = head;
		return (stack_test);
	}
	
	void	free_stack_test(t_stack *stack_test)
	{
		t_stack	*temp;
	
		while (stack_test)
		{
			temp = stack_test -> next;
			free(stack_test);
			stack_test = temp;
		}
	}

	void	test_function_big_value(void)
	{

		t_stack	*stack_test;
		int i;
		int	num;
		
		num = 37;
		// when call get_big_value(t_stack *stack) it should return 10
		stack_test = init_stack_test(num);
		i = get_big_value(stack_test);
		printf("When call get_big_value() it should return %d\n", num);
		printf("THE BIGGEST VALUE IS: [%d]\n", i);
		free_stack_test(stack_test);
	}

	
	void	test_function_get_last_node(void)
	{
		t_stack	*stack_test;
		t_stack *last_node;
		int		num;

		num = 15;
		stack_test = init_stack_test(num);
		// when call get_last_node(t_stack *stack) it should return last node which have 10 as value
		last_node = get_last_node(stack_test);
		printf("When call get_last_node() it should return last node which have [%d] as value\n", num);
		printf("THE VALUE OF THE LAST NODE IS: [%d]\n", last_node -> value);
		free_stack_test(stack_test);
	}


	test_function_big_value();	
	test_function_get_last_node();
}
