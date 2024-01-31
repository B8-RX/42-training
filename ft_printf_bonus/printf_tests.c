#include "ft_printf.h"

int	main(void)
{
	char	*str;
	char	c;
	char	*book;
	float	price;
	int		quantity;

	book = "The Alchimist";
	price = 15.51;
	quantity = 42;
	str = "just do it";
	c = 'T';
	// printf("\n\n\t---------------FT_PRINTF TESTS----------------\n\n");
	
	printf("==========================--SPECIFIER s, POSSIBLE CASES:--====================\n\n");
	ft_printf("clone:    |%-5.2s|\n", str);	
	printf("original: |%-5.2s|\n\n", str);	
	
	ft_printf("clone:    |%5.2s|\n", str);	
	printf("original: |%5.2s|\n\n", str);	
	
	ft_printf("clone:    |%.2s|\n", str);	
	printf("original: |%.2s|\n\n", str);	
	
	printf("==========================--SPECIFIER c, POSSIBLE CASES:--====================\n\n");
	ft_printf("clone:    |%c|\n", c);
	printf("original: |%c|\n\n", c);
	
	// ft_printf("clone:    |%010c|\n", c);
	// printf("original: |%010c|\n\n", c);
	
	ft_printf("clone:    |%-10c|\n", c);
	printf("original: |%-10c|\n\n", c);

	printf("==========================--SPECIFIER d and i, POSSIBLE CASES:--====================\n\n");
	ft_printf("clone:    |%010d|\n", 5);
	printf("original: |%010d|\n\n", 5);
	
	ft_printf("clone:    |%+010d|\n", 5);
	printf("original: |%+010d|\n\n", 5);
	
	ft_printf("clone:    |%+10d|\n", 5);
	printf("original: |%+10d|\n\n", 5);
	
	ft_printf("clone:    |%010d|\n", 5420);
	printf("original: |%010d|\n\n", 5420);
	
	ft_printf("clone:    |%10d|\n", -5);
	printf("original: |%10d|\n\n", -5);
	
	ft_printf("clone:    |%-10d|\n", -5);
	printf("original: |%-10d|\n\n", -5);
	
	ft_printf("clone:    |%010d|\n", -500);
	printf("original: |%010d|\n\n", -500);

	printf("==========================--SPECIFIER u, POSSIBLE CASES:--====================\n\n");
	ft_printf("clone:    |%050u|\n", 500);
	printf("original: |%050u|\n\n", 500);
	
	ft_printf("clone:    |%-50u|\n", 500);
	printf("original: |%-50u|\n\n", 500);
	
	ft_printf("clone:    |%-50u|\n", -500);
	printf("original: |%-50u|\n\n", -500);

	printf("==========================--SPECIFIER p, POSSIBLE CASES:--====================\n\n");
	ft_printf("clone:    |%p|\n", str);
	printf("original: |%p|\n\n", str);

	ft_printf("clone:    |%p|\n", book);
	printf("original: |%p|\n\n", book);

	printf("==========================--SPECIFIER  x and X POSSIBLE CASES:--====================\n\n");
	ft_printf("clone:    |%x|\n", 37);
	printf("original: |%x|\n\n", 37);

	ft_printf("clone:    |%X|\n", 37);
	printf("original: |%X|\n\n", 37);

	

	// ft_printf("\n======================END========================\n\n\n");

	return (0);
}
