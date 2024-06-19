/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 23:31:45 by ssghioua          #+#    #+#             */
/*   Updated: 2024/06/18 23:31:46 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include "./ft_printf_bonus/src/lib/ft_printf.h"
# include "./libft/src/include/libft.h"

typedef struct s_stack {
	char			*stack_name;
	int				value;
	int				index;
	int				operation_steps;
	bool			is_best_move;
	bool			in_upper_half;

	struct s_stack	*target;
	struct s_stack	*prev;
	struct s_stack	*next;
}	t_stack;

char		**split(char *str, const char splitter);
int			append_child(char *child, const char *value, const char splitter);
int			count_words(const char *str, const char splitter);
int			count_spaces(const char *str);
long int	ft_atol(const char *str);
int			get_len_value(const char *value);
void		*free_array_str(char **array);

void		init_stack_a(t_stack **stack_a, char **args, char **argv);	
void		init_new_node(t_stack **new_node, int val);
void		free_on_error(t_stack **stack, char ***args);
void		free_stack(t_stack *stack);

int			ft_is_digit(int c);
bool		is_sorted(t_stack *stack);
int			is_duplicate(t_stack *stack_a, int val);
int			is_numeric(char *args);

void		append_node(t_stack **stack, int val);
t_stack		*get_last_node(t_stack *stack);
int			get_stack_len(t_stack *stack);
t_stack		*get_big_node(t_stack *stack);
t_stack		*get_small_node(t_stack *stack);

void		update_nodes_a(t_stack *stack_a, t_stack *stack_b);
void		update_nodes_b(t_stack *stack_a, t_stack *stack_b);
void		update_index(t_stack *stack);
void		find_target_position_a(t_stack *stack_a, t_stack *stack_b);
void		find_target_position_b(t_stack *stack_a, t_stack *stack_b);
void		count_move_steps_a(t_stack *stack_a, t_stack *stack_b);
void		count_move_steps_b(t_stack *stack_a, t_stack *stack_b);
void		set_best_move(t_stack *stack_a);

t_stack		*get_best_move_node(t_stack *stack);

void		move_to_stack_b(t_stack **stack_a, t_stack **stack_b);
void		move_to_stack_a(t_stack **stack_a, t_stack **stack_b);

void		set_up_rr(t_stack **stack_a, t_stack **stack_b,
				t_stack *best_move_node);
void		set_up_rrr(t_stack **stack_a, t_stack **stack_b,
				t_stack *best_move_node);
void		ready_for_move(t_stack **stack, t_stack *candidate,
				char stack_name);

void		small_chunk_at_top(t_stack **stack_a);
void		sort_three(t_stack	**stack_a);
void		sort_big(t_stack **stack_a);

void		sa(t_stack **stack_a, int print);
void		sb(t_stack **stack_b, int print);
void		ss(t_stack **stack_a, t_stack **stack_b, int print);
void		ra(t_stack **stack_a, int print);
void		rb(t_stack **stack_b, int print);
void		rr(t_stack **stack_a, t_stack **stack_b, int print);
void		rra(t_stack **stack_a, int print);
void		rrb(t_stack **stack_b, int print);
void		rrr(t_stack **stack_a, t_stack **stack_b, int print);
void		pa(t_stack **stack_a, t_stack **stack_b, int print);
void		pb(t_stack **stack_a, t_stack **stack_b, int print);

// TESTS FUNCTIONS
// void		tests_stack_utils_functions(void);
// void		tests_operations_functions(void);
// void		init_stack_test(t_stack **stack_test, int nodes);
// void		free_stack_test(t_stack *stack_test);
// int		random_number(int min_num, int max_num);
// void		ft_print_all_stacks(t_stack *stack_a, t_stack *stack_b);

#endif // ! PUSH_SWAP_H
