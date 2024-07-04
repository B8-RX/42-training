#include <mlx.h>
#include "get_next_line_bonus.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_map {
	char	*map_path;
	int		player;
	int		exit;
	int		empty;
	int		wall;
	char	*line;
	size_t	line_length;
	int		total_lines;
	int		collectibles;
} t_map;

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	get_map_length(int fd)
{
	int		len;
	char	*line;
	
	len = 0;
	line = get_next_line(fd);
	while (line)
	{
		len++;
		free(line);
		line = get_next_line(fd);
	}	
	if (line)
		free(line);
	return (len);
}

bool	is_square(char *map_path)
{
	size_t	first_row_len;
	int		fd;
	char	*line;

	fd = open(map_path, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		return (false);
	first_row_len = ft_strlen(line);
	while (line)
	{
		if (ft_strlen(line) != first_row_len)
			return (free(line), false);
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	printf("MAP IS A VALID SQUARE\n");
	return (true);
}


bool	is_valid_walls(char *map_path, int total_rows)
{
	int		fd;
	char	*curr_line;
	size_t	col;
	size_t	row;
	size_t	line_length;

	fd = open(map_path, O_RDONLY);
	curr_line = get_next_line(fd);
	if (!curr_line)
		return (false);
	col = -1;
	row = 1;
	while (curr_line)
	{
		line_length = ft_strlen(curr_line);
		if (row == 1 || row == total_rows)
			while (col < line_length - 1)
			{
				if (curr_line[col] != '1')
					return (free(curr_line), false);
				col++;
			}
		else
			if (curr_line[col] != '1' || curr_line[line_length - 2] != '1')
				return (free(curr_line), false);
		free(curr_line);
		curr_line = get_next_line(fd);
		col = 0;
		row++;
	}
	printf("VALID WALLS\n");
	return (true);
}

int	get_total_rows(char *map_path)
{
	int		fd;
	char	*line;
	size_t	row;

	fd = open(map_path, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		return (0);
	row = 0;
	while (line)
	{
		row++;
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (row);	
}

bool	is_valid_fill(char *map_path, int total_rows)
{
	int		fd;
	char	*line;
	size_t	line_length;
	size_t	col;
	size_t	row;

	fd = open(map_path, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		return (false);
	col = 1;
	row = 2;
	while (line)
	{
		if (row > 1 && row < total_rows)
		free(line);
		line = get_next_line(fd);
		row++;
	}

}

int verify_map(char *map_path)
{
	t_map	*map_data;
	int		total_rows;

	map_data = malloc(sizeof(t_map));
	if (!map_data)
		return (0);
	map_data -> map_path = map_path;
	map_data -> player = 0;
	map_data -> exit = 0;
	map_data -> empty = 0;
	map_data -> wall = 0;

	// verify all lines same LENGTH
	// verify first line and last line are only 1 and first char and last char in all rows are also 1
	// verify in the middle after the first char and the last char there are only /PE1CO/
	// verify that the Player P can access the collectibles and access the Exit E

	if (!is_square(map_path))
		return (printf("NOT VALID SQUARE\n"), free(map_data), 0);
	total_rows = get_total_rows(map_path);
	if (!is_valid_walls(map_path, total_rows))
		return (printf("NOT VALID WALLS\n"), free(map_data), 0);
	if (!is_valid_fill(map_path, total_rows))
		return (free(map_data), 0);
	// if (!is_valid_player_path(map_path))
	// 	return (free(map_data), 0);

	// fd = open(map_path, O_RDONLY);
	// map_data -> total_lines = get_map_length(fd);
	// if (map_data -> total_lines < 4)
	// 	return (free(map_data), 0);
	// fclose(fd);
	// fd = open(map_path, O_RDONLY);
	// map_data -> line = get_next_line(fd);
	// map_data -> line_length = ft_strlen(map_data -> line);
	// 
	// while (map_data -> line)
	// {
	//
	// }
	//
	// if (!check_line(map_data, fd))
	// 	return (free(map_data), 0);
	printf("total_lines: %d\n", total_rows);
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
