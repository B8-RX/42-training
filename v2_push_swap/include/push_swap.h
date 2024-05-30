

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>


typedef struct s_stack {
	char	*stack_name;
	int		value;
	int		index;
	int		operations_cost;
	int		is_best_move;

	struct s_stack	*target_node;
	struct s_stack	*prev;
	struct s_stack	*next;
}	t_stack;

char		**split(char *str, const char splitter);
int			append_child(char *child, const char *value, const char splitter);
int			count_words(const char *str, const char splitter);
int			ft_is_digit(int c);
int			count_spaces(const char *str);
long int	ft_atol(const char *str);
int			get_len_value(const char *value);
void		*free_array_str(char **array);

void		init_stack_a(t_stack **stack_a, char **args, char **argv);	
int			is_numeric(char *args);
void		free_on_error(t_stack *stack, char **args);
void		free_stack(t_stack *stack);
int			is_duplicate(t_stack *stack_a, int val);
void		append_node(t_stack **stack, int val);
t_stack		*get_last_node(t_stack *stack);
int			get_stack_len(t_stack *stack);
int			get_big_value(t_stack *stack);
int			get_small_value(t_stack *stack);

void		sa(t_stack **stack_a, int print);
void		sb(t_stack **stack_b, int print);
void		ss(t_stack **stack_a, t_stack **stack_b, int print);
void		ra(t_stack **stack_a, int print);
void		rb(t_stack **stack_b, int print);

void		tests_functions(void);
#endif // ! PUSH_SWAP_H



// init stack
//  - errors checking
//	- populate with values
// 
// check if stack len is < 3 or == 3 or > 3
//	if < 3 trigger sa()
//	if == 3 trigger mini sort function
//	if > 3 trigger big sort function
//
//
//
// TODO:
//	- CREATE OPERATIONS FUNCTIONS
//	- CREATE LITTLE SORT FUNCTION
//	- CREATE BIG SORT FUNCTION

