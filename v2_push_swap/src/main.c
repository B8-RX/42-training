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
