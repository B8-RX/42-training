

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>


typedef struct s_stack_node {
	char	*stack_name;
	int		value;
	int		index;
	int		operations_cost;
	int		is_best_move;

	struct s_stack_node	*target_node;
	struct s_stack_node	*prev;
	struct s_stack_node	*next;
}	t_stack_node;

char		**split(char *str, const char splitter);
int			append_child(char *child, const char *value, const char splitter);
int			count_words(const char *str, const char splitter);
int			ft_is_digit(int c);
int			count_spaces(const char *str);
long int	ft_atol(const char *str);
int			get_len_value(const char *value);
void		*free_array_str(char **array);
void		init_stack_a(t_stack_node **stack_a, char **args, char **argv);	
int			is_numeric(char *args);
void		free_on_error(t_stack_node *stack, char **args);
void		free_stack(t_stack_node *stack);
int			is_duplicate(t_stack_node *stack_a, int val);
void		append_node(t_stack_node **stack, int val);


#endif // ! PUSH_SWAP_H
