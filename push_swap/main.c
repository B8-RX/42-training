/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 01:11:41 by ssghioua          #+#    #+#             */
/*   Updated: 2024/03/29 01:11:46 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./push_swap.h"

int	main(int argc, char **argv)
{

	t_stack	*stack_a;
	int		*sorted_entries;

	stack_a = malloc (sizeof(t_stack));
	if (!stack_a)
		return (0);
	sorted_entries = NULL;
	if (argc == 1)
		return (0);
	ft_handle_args(argc, argv, &stack_a);
	// if (stack_a)
		// sorted_entries = ft_sort_input(&stack);
	// else
		// return ft_print_error();

	return (0);
}

t_stack	*ft_handle_args(int argc, char **argv, t_stack **stack)
{
	t_stack	*stack_a;
	char	**tmp;
	int		i;

	stack_a = *stack; 
	tmp = NULL;
	if (argc == 2)
		tmp = ft_handle_second_arg(argv);
	else
		tmp = argv + 1;
	i = -1;
	while (tmp[++i])
	{
		printf("word: |%s|\n", tmp[i]);
		stack_a -> value = ft_atoi(tmp[i]);
		stack_a -> previous = NULL;
		stack_a -> next = NULL;
		if (argc == 2)
			free(tmp[i]);
	}
	if (argc == 2 && tmp)
		free(tmp);
	
	return (stack_a);
}

char	**ft_handle_second_arg(char **argv)
{
	char	**args;

	args = ft_split(argv[1], ' ');
	return (args);
}

/*

TODO


 # verifier le nombre d'argument (argc)
	ok* si le nombre d'argument == 1 ===> return (0)


 # traiter les arguments ====> ft_handle_args().
	(en cas d'erreur de format, afficher un message d'erreur sur le stderror)
	ok- si le nombre d'arguments == 2  ===> ft_handle_second_args()
	ok- split les arguments  ====> ft_split_args()
	- transformer les nombres en format char* en int  ====> ft_atoi()
	- verifier qu'il n'y a pas de doublons  ===> ft_check_if_duplicate_nbr()
	- assigner chaque arguments dans la liste circulaire (stack a) ==> ft_put_entries_in_stack()
 
 # trier les arguments par ordre croissant  ====> ft_sort_input()
	-
	-
	-
	-
	-
 
*/
