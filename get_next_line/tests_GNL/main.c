


// #include "../gnl_v3_bonus_linked_list/get_next_line.h"
#include "../gnl_v3_bonus_linked_list/get_next_line_bonus.h"

int	main(void)
{
	int		fd1;
	int		fd2;
	int		fd3;
	char	*next_line_fd1;
	char	*next_line_fd2;
	char	*next_line_fd3;
	int		nb_line_fd1;
	int		nb_line_fd2;
	int		nb_line_fd3;

	nb_line_fd1 = 0;
	nb_line_fd2 = 0;
	nb_line_fd3 = 0;
	fd1 = open("./1651.txt", O_RDONLY);
	fd2 = open("./1723.txt", O_RDONLY);
	fd3 = open("./523.txt", O_RDONLY);
	if (fd1 == -1 || fd2 == -1 || fd3 == -1)
		return (0);
	next_line_fd1 = get_next_line(fd1);
	next_line_fd2 = get_next_line(fd2);
	next_line_fd3 = get_next_line(fd3);
	while(next_line_fd1 != NULL || next_line_fd2 != NULL || next_line_fd3 != NULL)
	{
		if (next_line_fd1)
		{
			nb_line_fd1++;
			printf("\n==========================================================\n\n");
			printf("fd 1, line |%d|:\n|%s|\n", nb_line_fd1, next_line_fd1);
			printf("\n==========================================================\n\n");	
			free(next_line_fd1);
			next_line_fd1 = NULL;
			next_line_fd1 = get_next_line(fd1);
			printf("/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		}
		if (next_line_fd2)
		{
			nb_line_fd2++;
			printf("\n==========================================================\n\n");
			printf("fd 2, line |%d|:\n|%s|\n", nb_line_fd2, next_line_fd2);
			printf("\n==========================================================\n\n");	
			free(next_line_fd2);
			next_line_fd2 = NULL;
			next_line_fd2 = get_next_line(fd2);
			printf("/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		}
		if (next_line_fd3)
		{
			nb_line_fd3++;
			printf("\n==========================================================\n\n");
			printf("fd 3, line |%d|:\n|%s|\n", nb_line_fd3, next_line_fd3);
			printf("\n==========================================================\n\n");	
			free(next_line_fd3);
			next_line_fd3 = NULL;
			next_line_fd3 = get_next_line(fd3);
			printf("/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		}
	}
	free(next_line_fd1);
	free(next_line_fd2);
	free(next_line_fd3);
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}

