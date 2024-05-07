
#include "./include/push_swap.h"

int	main(int argc, char **argv)
{
	t_stack_node	*stack_a;
	// t_stack_node	*stack_b;
	//
	stack_a = NULL;
	// stack_b = NULL;
	char **args;

	args = NULL;
	if (argc == 1 || ( argc == 2 && !argv[1][0]))
		return (-1);
	if (argc == 2)
		args = split(argv[1], ' ');
	init_stack_a(&stack_a, args, argv + 1);
	if (args)
		free_array_str(args);
	return (0);
}

void	init_stack_a(t_stack_node **stack_a, char **args, char **argv)
{
	char	**array;
	long	val;

	if (!args)
		array = argv;
	else
		array = args;
	while (*array)
	{
		if (!is_numeric(*array))
			free_on_error(*stack_a, args);
		val = ft_atol(*array);
		if (val < INT_MIN || val > INT_MAX)
			free_on_error(*stack_a, args);
		// if (is_duplicate(*stack_a, val))
		// 	error_free(*stack_a, args);
		array++;
	}
	printf("TEST SYNTAX OK\n");
	*stack_a = NULL;
	// check if duplicate
	// create stack
	//		null for the last next and null for the first prev
}

void	free_on_error(t_stack_node *stack, char **args)
{
	t_stack_node	*tmp;
	int				i;

	tmp = stack;
	i = 0;
	if (args)
	{
		while (args[i])
			free(args[i++]);
		free(args);
	}
	if (stack)
	{
		while (stack)
		{
			tmp = stack -> next;
			free(stack);
			stack = tmp;
		}
	}
	exit(1);
}

int	is_numeric(char *argv)
{
	char	*arg;

	arg = argv;
	if (!(*arg >= '0' && *arg <= '9') && (*arg != '-') && (*arg != '+'))
		return (0);
	else if ((*arg == '-' || *arg == '+') && !(*(arg + 1) >= '0' && *(arg + 1) <= '9'))
		return (0);
	arg++;
	while (*arg)
	{
		if (!(*arg >= '0' && *arg <= '9'))
			return (0);
		arg++;
	}
	return (1);
}
