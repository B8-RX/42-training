/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 22:32:57 by ssghioua          #+#    #+#             */
/*   Updated: 2024/06/18 22:32:59 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/push_swap.h"

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
			tmp = (*stack)-> next;
			free(*stack);
			*stack = tmp;
		}
	}
}

void	free_stack(t_stack *stack)
{
	t_stack	*tmp;

	if (!stack)
		return ;
	while (stack -> next)
	{
		tmp = stack -> next;
		free(stack);
		stack = NULL;
		stack = tmp;
	}
	free(stack);
}

void	*free_array_str(char **array)
{
	int	i;

	i = 0;
	if (!*array)
		return (NULL);
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
	return (NULL);
}