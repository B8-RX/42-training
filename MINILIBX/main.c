#include <mlx.h>
#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct s_map {
	int player;
	int	exit;
	int empty;
	int wall;
} t_map;

int	check_line(char *line, int line_type)
{
	int		i;
	t_map	map;

	map.player = 0;
	map.exit = 0;
	map.empty = 0;
	map.wall = 0;
	if (!line)
		return (0);
	i = 0;
	fprintf(stderr, "line = %s\n", line);
	//printf("line = %s\n", line);
	while (line[i])
	{
		if (line_type == -1 && line[i] != '1' && line[i] != '\n')
		{
			printf("WALL ERROR\n");
			return (0);
		}
		if (line_type == 0 && (!ft_strchr("PE10\n", line[i]) || (map.player > 1 || map.exit > 1)))			
			return (printf("PE10 ERROR \n"), 0);
		if (line_type == 0 && line[i] == 'P')
			map.player++;
		if (line_type == 0 && line[i] == 'E')
			map.exit++;
		if (line[0] != '1' || line[ft_strlen(line) - 2] != '1')
			return (printf("BORDER ERROR\n"), 0);
		i++;
	}
	return (1);
}


int verify_map(char *map)
{
	char	*line;
	int		fd;
	int		total_lines;
	int		first_line;
	int		last_line;
	int		i;

	fd = open(map, O_RDONLY);
	total_lines = 0;
	line = get_next_line(fd);
	first_line = 0;
	while (line)
	{
		total_lines++;
		free(line);
		line = get_next_line(fd);
	}	
	free(line);
	last_line = total_lines;
	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	while (line && ++i)
	{
		if (i == 1 && !check_line(line, -1))
			return (free(line), 0);
		else if (i == last_line	&& !check_line(line, -1))
			return (free(line), 0);
		else if (!check_line(line, 0))
			return (free(line), 0);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	printf("total_lines: %d\n", total_lines);
	return (1);
}


int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;

	if (argc < 2)
		return (0);
	printf("argv: %s\n", argv[1]);	
	mlx = mlx_init();
	if (!mlx)
		return (0);
	if (!verify_map(argv[1]))
	{
		printf("ERROR\n");
		free(mlx);
		return (0);
	}
	mlx_win = mlx_new_window(mlx, 800, 600, "test window");
	mlx_loop(mlx);

	return (0);
}
