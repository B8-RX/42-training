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
	printf("\n\n\t\t\t---------------FT_PRINTF TESTS----------------\n\n");
	
	printf("==========================--SPECIFIER s, WORKING CASES:--====================\n\n");
	ft_printf("clone:    |%s|\n", str);	
	printf("original: |%s|\n\n", str);	

	printf("#1\n");	
	ft_printf("clone:    |%-5.4s|\n", str);	
	printf("original: |%-5.4s|\n\n", str);	

	printf("#2\n");
	ft_printf("clone:    |%15.7s|\n", str);	
	printf("original: |%15.7s|\n\n", str);	

	printf("#3\n");
	ft_printf("clone:    |%.2s|\n", str);	
	printf("original: |%.2s|\n", str);	
	printf("##TEST RETURN VALUE##\n");
	ft_printf("clone:    |%d|\n", ft_printf("|%.2s|\n", str));
	printf("original: |%d|\n\n", printf("|%.2s|\n", str));


	printf("==========================--SPECIFIER c, WORKING CASES:--====================\n\n");
	ft_printf("clone:    |%c|\n", c);
	printf("original: |%c|\n\n", c);

	printf("#4\n");
	ft_printf("clone:    |%10c|\n", c);
	printf("original: |%10c|\n\n", c);

	printf("#5\n");
	ft_printf("clone:    |%-10c|\n", c);
	printf("original: |%-10c|\n", c);
	printf("##TEST RETURN VALUE##\n");
	ft_printf("clone:    |%d|\n", ft_printf("|%-10c|\n", c));
	printf("original: |%d|\n\n", printf("|%-10c|\n", c));

	printf("==========================--SPECIFIER d and i, WORKING CASES:--====================\n\n");
	ft_printf("clone:    |% d|\n", 5);
	printf("original: |% d|\n\n", 5);

	printf("#6\n");
	ft_printf("clone:    |%010d|\n", 5);
	printf("original: |%010d|\n\n", 5);

	printf("#7\n");
	ft_printf("clone:    |%+010d|\n", 5);
	printf("original: |%+010d|\n\n", 5);

	printf("#8\n");
	ft_printf("clone:    |%-+10.2d|\n", 5);
	printf("original: |%-+10.2d|\n\n", 5);

	printf("#8.1\n");
	ft_printf("clone:    |%+10.2d|\n", 50);
	printf("original: |%+10.2d|\n\n", 50);

	printf("#9\n");
	ft_printf("clone:    |%010.2d|\n", 5);
	printf("original: |%010.2d|\n\n", 5);

	printf("#10\n");
	ft_printf("clone:    |%+0.2d|\n", 5);
	printf("original: |%+0.2d|\n\n", 5);

	printf("#11\n");
	ft_printf("clone:    |%010.4d|\n", 5420);
	printf("original: |%010.4d|\n\n", 5420);

	printf("#12\n");
	ft_printf("clone:    |%10d|\n", -5);
	printf("original: |%10d|\n\n", -5);

	printf("#13\n");
	ft_printf("clone:    |%-10d|\n", -5);
	printf("original: |%-10d|\n\n", -5);	

	printf("#14\n");
	ft_printf("clone:    |%010d|\n", -500);
	printf("original: |%010d|\n", -500);
	printf("##TEST RETURN VALUE##\n");
	ft_printf("clone:    |%d|\n", ft_printf("|%010d|\n", -500));
	printf("original: |%d|\n\n", printf("|%010d|\n", -500));
	
	printf("==========================--SPECIFIER u, WORKING CASES:--====================\n\n");
	ft_printf("clone:    |%u|\n", 500);
	printf("original: |%u|\n\n", 500);

	printf("#15\n");
	ft_printf("clone:    |%050u|\n", 500);
	printf("original: |%050u|\n\n", 500);

	printf("#16\n");
	ft_printf("clone:    |%-50u|\n", 500);
	printf("original: |%-50u|\n\n", 500);

	printf("#17\n");
	ft_printf("clone:    |%-50u|\n", -500);
	printf("original: |%-50u|\n", -500);
	printf("##TEST RETURN VALUE##\n");
	ft_printf("clone:    |%d|\n", ft_printf("|%-50u|\n", -500));
	printf("original: |%d|\n\n", printf("|%-50u|\n", -500));			

	printf("==========================--SPECIFIER p, WORKING CASES:--====================\n\n");
	printf("#18\n");
	ft_printf("clone:    |%p|\n", str);
	printf("original: |%p|\n\n", str);

	printf("#19\n");
	ft_printf("clone:    |%p|\n", book);
	printf("original: |%p|\n\n", book);
	printf("##TEST RETURN VALUE##\n");
	ft_printf("clone:    |%d|\n", ft_printf("|%p|\n", book));
	printf("original: |%d|\n\n", printf("|%p|\n", book));

	printf("==========================--SPECIFIER  x and X WORKING CASES:--====================\n\n");
	printf("#20\n");
	ft_printf("clone:    |%x|\n", 42);
	printf("original: |%x|\n\n", 42);

	printf("#21\n");
	ft_printf("clone:    |%X|\n", 42);
	printf("original: |%X|\n\n", 42);

	printf("#22\n");
	ft_printf("clone:    |%#x|\n", 42);
	printf("original: |%#x|\n\n", 42);

	printf("#23\n");
	ft_printf("clone:    |%#X|\n", 42);
	printf("original: |%#X|\n", 42);
	printf("##TEST RETURN VALUE##\n");
	ft_printf("clone:    |%d|\n", ft_printf("|%#X|\n", 42));
	printf("original: |%d|\n\n", printf("|%#X|\n", 42));

	printf("==========================-- %% --====================\n\n");
	printf("#24\n");
	ft_printf("clone:    test percent sign: |%%|\n");
	printf("original: test percent sign: |%%|\n\n");

	// printf("\t\t\t\tXXXXXXXXXXXXXXXXXXXXXXX\n");
	// printf("\t\t\t\tXXXXXXXXXXXXXXXXXXXXXXX\n");
	// printf("\t\t\t\tXXXXXXXXXXXXXXXXXXXXXXX\n");
	// printf("\t\t\t\tXXXXXXXXXXXXXXXXXXXXXXX\n\n");
	// printf("\t====XXXXX====--ERROR CASES (need compilation without flags):--====XXXXX====\n\n");
	//
	// printf("=======XXXXX======--SPECIFIER s, ERROR CASES:--====XXXXX====\n\n");
	// printf("##s##1\n");	
	// ft_printf("clone:    |%|\n", str);	
	// printf("original: |%|\n\n", str);	
	//
	// printf("##s##2\n");	
	// ft_printf("clone:    |%- 5.4s|\n", str);	
	// printf("original: |%- 5.4s|\n\n", str);	
	//
	// printf("##s##3\n");	
	// ft_printf("clone:    |%- + 5.4s|\n", str);	
	// printf("original: |%- + 5.4s|\n\n", str);	
	// 
	// printf("##s##4\n");	
	// ft_printf("clone:    |%- #+ 5.4s|\n", str);	
	// printf("original: |%- #+ 5.4s|\n\n", str);	
	// 
	// printf("=======XXXXX======--SPECIFIER d and i, ERROR CASES:--=====XXXXX===\n\n");
	// printf("##di##1\n");
	// ft_printf("clone:    |%010-d|\n", 5);
	// printf("original: |%010-d|\n\n", 5);
	//
	// printf("##di##2\n");
	// ft_printf("clone:    |%+-010d|\n", 5);
	// printf("original: |%+-010d|\n\n", 5);
	//
	// printf("##di##3\n");
	// ft_printf("clone:    |%- +10.2d|\n", 5);
	// printf("original: |%- +10.2d|\n\n", 5);
	//
	// printf("##di##4\n");
	// ft_printf("clone:    |%- +10#.2d|\n", 5);
	// printf("original: |%- +10#.2d|\n\n", 5);
	// 
	// printf("##di##5\n");
	// ft_printf("clone:    |%- #+10.2d|\n", 5);
	// printf("original: |%- #+10.2d|\n\n", 5);
	// 
	// printf("##di##6\n");
	// ft_printf("clone:    |%- .+10.2d|\n", 5);
	// printf("original: |%- .+10.2d|\n\n", 5);

	printf("\n\n\t\t\t---------------END OF TESTS----------------\n\n");

	return (0);
}
