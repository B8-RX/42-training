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

	stack_a = NULL;
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

t_stack	*ft_handle_args(int argc, char **argv, t_stack **stack_a)
{
	char	**tmp;
	int		i;

	tmp = NULL;
	if (argc == 2)
		tmp = ft_handle_second_arg(argv);
	i = 0;
	if (tmp)
	{
		while (tmp[i])
		{
			printf("word: |%s|\n", tmp[i]);
			free(tmp[i]);
			i++;
		}
		free(tmp);			
	}
	return (*stack_a);
}

char	**ft_handle_second_arg(char **argv)
{
	char	*args;

	args = argv[1];
	return (ft_split(args, ' '));
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
