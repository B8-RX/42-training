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

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	char	**args;

	args = NULL;
	stack_a = NULL;
	if (argc == 1 || (argc == 2 && !argv[1][0]))
		return (-1);
	if (argc == 2)
		args = split(argv[1], ' ');
	init_stack_a(&stack_a, args, argv + 1);
	free_array_str(args);
	if (!is_sorted(stack_a))
	{
		if (get_stack_len(stack_a) == 2)
			sa(&stack_a, 1);
		else if (get_stack_len(stack_a) == 3)
			sort_three(&stack_a);
		else
			sort_big(&stack_a);
	}
	free_stack(stack_a);
	return (0);
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

size_t	ft_strlen(const char *str)
{
	size_t	len;
	int		i;

	len = 0;
	i = 0;
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
