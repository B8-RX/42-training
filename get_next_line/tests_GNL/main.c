


// #include "../gnl_v3_bonus_linked_list/get_next_line.h"
#include "../gnl_v3_bonus_linked_list/get_next_line_bonus.h"

int	main(void)
{
	int		fd;
	char	*next_line;
	int		nb_line;

	nb_line = 0;
	fd = open("./1651.txt", O_RDONLY);
	if (fd == -1)
		return (0);
	next_line = get_next_line(fd);
	while(nb_line != -1 && next_line != NULL)
	{
		nb_line++;
		printf("\n==========================================================\n\n");
		printf("total lines |%d|:\n|%s|\n", nb_line, next_line);
		printf("\n==========================================================\n\n");	
		free(next_line);
		next_line = NULL;
		if (nb_line == 3)
			nb_line = -1;
		next_line = get_next_line(fd);
		if (next_line)
			printf("/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
	}
	free(next_line);
	close(fd);
	return (0);
}

