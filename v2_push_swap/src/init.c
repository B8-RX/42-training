/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 22:58:34 by ssghioua          #+#    #+#             */
/*   Updated: 2024/06/18 22:58:35 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/push_swap.h"

void	init_stack_a(t_stack **stack_a, char **args, char **argv)
{
	char	**entries;
	long	val;

	if (!args)
		entries = argv;
	else
		entries = args;
	while (*entries)
	{
		if (!is_numeric(*entries))
		{
			free_on_error(stack_a, &args);
			exit(1);
		}
		val = ft_atol(*entries);
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
		entries++;
	}
}

void	init_new_node(t_stack **new_node, int val)
{
	(*new_node)-> value = val;
	(*new_node)-> index = 0;
	(*new_node)-> operation_steps = 0;
	(*new_node)-> is_best_move = false;
	(*new_node)-> in_upper_half = false;
	(*new_node)-> target = NULL;
	(*new_node)-> prev = NULL;
	(*new_node)-> next = NULL;
}

void	append_node(t_stack **stack, int val)
{
	t_stack	*new_node;
	t_stack	*curr;

	if (!stack)
		return ;
	new_node = malloc(sizeof(t_stack));
	if (!new_node)
		return ;
	init_new_node(&new_node, val);
	if (!(*stack))
	{
		new_node -> prev = NULL;
		*stack = new_node;
	}
	else
	{
		curr = get_last_node(*stack);
		curr -> next = new_node;
		new_node -> prev = curr;
	}	
}
