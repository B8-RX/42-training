/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 22:55:23 by ssghioua          #+#    #+#             */
/*   Updated: 2024/06/18 22:55:28 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/push_swap.h"

int	is_duplicate(t_stack *stack_a, int val)
{
	t_stack	*curr;

	curr = stack_a;
	if (!stack_a)
		return (0);
	while (curr)
	{
		if (curr -> value == val)
			return (1);
		curr = curr -> next;
	}
	return (0);
}

int	is_numeric(char *argv)
{
	char	*arg;

	arg = argv;
	if (!argv)
		return (0);
	if (!(*arg >= '0' && *arg <= '9') && (*arg != '-') && (*arg != '+'))
		return (0);
	else if ((*arg == '-' || *arg == '+')
		&& !(*(arg + 1) >= '0' && *(arg + 1) <= '9'))
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

bool	is_sorted(t_stack *stack)
{
	if (!stack)
		return (1);
	while (stack -> next)
	{
		if (stack -> value > stack -> next -> value)
			return (false);
		stack = stack -> next;
	}
	return (true);
}

int	ft_is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
