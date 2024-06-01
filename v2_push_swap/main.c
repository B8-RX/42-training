/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:03:56 by ssghioua          #+#    #+#             */
/*   Updated: 2024/05/16 18:03:59 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./include/push_swap.h"

void	print_values(t_stack *stack)
{
	while (stack)
	{
		printf("[%d]\n", stack -> value);
		stack = stack -> next;
	}
}

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	// t_stack	*stack_b;

	stack_a = NULL;
	// stack_b = NULL;
	char	**args;
	int		stack_len;	

	args = NULL;
	if (argc == 1 || ( argc == 2 && !argv[1][0]))
		return (-1);
	if (argc == 2)
		args = split(argv[1], ' ');
	// if (argc == 2 && !ft_is_digit(**args))
	// 	return (free_array_str(args), -1);
	init_stack_a(&stack_a, args, argv + 1);
	stack_len = get_stack_len(stack_a);
	print_values(stack_a);
	if (stack_len > 1 && stack_len < 3 && stack_a -> value > stack_a -> next -> value)
		 sa(&stack_a, 1);
	// else if (stack_len == 3)
		// sort_three(&stack_a);
	// else
	// 	sort_big(&stack_a, &stack_b);
	print_values(stack_a);
	if (args)
		free_array_str(args);
	if (stack_a)
		free_stack(stack_a);
	
	tests_functions();
	return (0);
}

void	init_stack_a(t_stack **stack_a, char **args, char **argv)
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
			free_on_error(stack_a, &args);
		val = ft_atol(*array);
		if (val < INT_MIN || val > INT_MAX)
		{
			free_on_error(stack_a, &args);
			exit(1);
		}
		if (is_duplicate(*stack_a, val))
		{
			free_on_error(stack_a, &args);
			exit(1);
		}
		append_node(stack_a, val);
		array++;
	}
	printf("TEST SYNTAX OK\n");
}

void	append_node(t_stack **stack, int val)
{
	t_stack	*new_node;
	t_stack	*curr;

	new_node = malloc(sizeof(t_stack));
	if (!new_node)
		return ;
	new_node -> value = val;
	if (!(*stack))
	{
		new_node -> prev = NULL;
		new_node -> next = NULL;
		*stack = new_node;
	}
	else
	{
		curr = *stack;
		while (curr -> next)
			curr = curr -> next;
		curr -> next = new_node;
		new_node -> prev = curr;
		new_node -> next = NULL;
	}	
}

int	is_duplicate(t_stack *stack_a, int val)
{
	t_stack *curr;

	curr = stack_a;
	if (!stack_a)
		return (0);
	while (curr)
	{
		if (curr -> value == val)
		{
			printf("ERROR DUPLICATED NUMBER\n");
			return (1);
		}
		curr = curr -> next;
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;
	int		i;

	len = 0;
	i	= 0;
	while (str[i++])
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	len_src;

	i = 0;
	if (!dest || !src)
		return (0);
	len_src = ft_strlen(src);
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (len_src);
}

void	free_on_error(t_stack **stack, char ***args)
{
	t_stack	*tmp;
	int		i;

	tmp = *stack;
	i = 0;
	if (args && *args)
	{
		while ((*args)[i])
		{
			free((*args)[i]);
			(*args)[i] = NULL;
			i++;
		}
		free(*args);
		*args = NULL;
	}
	if (stack && *stack)
	{
		while (*stack)
		{
			tmp = (*stack) -> next;
			free(*stack);
			*stack = tmp;
		}
	}
}

void	free_stack(t_stack *stack)
{
	t_stack	*tmp;

	while (stack -> next)
	{
		tmp = stack -> next; 
		free(stack);
		stack = NULL;
		stack = tmp;
	}
	free(stack);
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
