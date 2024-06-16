
#include "./include/push_swap.h"

void	ft_print_all_stacks(t_stack *stack_a, t_stack *stack_b)
{
	int		len_stack_a;
	int		len_stack_b;
	int		diff_len;
	char	larger_stack_name;
	int		larger_stack;

	len_stack_a = get_stack_len(stack_a);
	len_stack_b = get_stack_len(stack_b);
	diff_len = 0;
	if (len_stack_a >= len_stack_b)
	{
		larger_stack_name = 'A'; 
		larger_stack = len_stack_a;
		diff_len = len_stack_a - len_stack_b;
	}
	else
	{
		larger_stack_name = 'B';
		larger_stack = len_stack_b;
		diff_len = len_stack_b - len_stack_a;
	}
	printf("\n");
	while (larger_stack > 0)
	{
		if (diff_len)
		{
			if (larger_stack_name == 'A')
			{
				printf("|%-7d", stack_a -> value);
				printf("%7c|\n", ' ');
				stack_a = stack_a -> next;
			}
			else
			{
				printf("|%-7c", ' ');
				printf("%7d|\n", stack_b -> value);
				stack_b = stack_b -> next;
			}
			diff_len--;
		}
		else 
		{
			printf("|%-7d", stack_a -> value);
			printf("%7d|\n", stack_b -> value);
			stack_a = stack_a -> next;
			stack_b = stack_b -> next;
		}
		larger_stack--;
	}
	printf("%-9s", "###");
	printf("%7s\n", "###");
	printf("%-8s", "A");
	printf("%8s \n", "B");
	printf("%-9s", "###");
	printf("%7s\n", "###");
	printf("\n");
}
