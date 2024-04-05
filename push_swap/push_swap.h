/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 01:52:00 by ssghioua          #+#    #+#             */
/*   Updated: 2024/04/04 01:52:01 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_stack {
	int				value;
	struct s_stack	*previous;
	struct s_stack	*next;
}	t_stack;


t_stack	*ft_handle_args(int args_len, char **args, t_stack **stack);
char	**ft_handle_second_arg(char **argv);
int		ft_count_words(char *str, char splitter);
int		ft_is_digit(char c);
char	*ft_print_error(void);
int		ft_count_spaces(char *str);
int		ft_count_value_len(char *value);
char	**ft_split(char *str, char splitter);
void	*ft_free_parent_array(char **parent_array);
int		ft_push_value(char *parent_array, char *value, char splitter);






