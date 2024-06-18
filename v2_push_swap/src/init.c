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
			free_on_error(stack_a, &args);
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
