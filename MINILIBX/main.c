#include "so_long.h"

bool	is_map_square(t_map *map_data)
{
	size_t	first_row_len;
	char	**matrix;
	int		i;

	i = 0;
	matrix = map_data -> matrix;
	first_row_len = ft_strlen(matrix[i++]);
	while (matrix[i])
	{
		if (ft_strlen(matrix[i]) != first_row_len)
			return (false);
		i++;
	}
	return (true);
}


bool	is_valid_walls(t_map *map_data)
{
	size_t	col;
	size_t	row;
	size_t	line_length;
	char	**matrix;

	matrix = map_data -> matrix;
	col = -1;
	row = 0;
	while (matrix[row])
	{
		line_length = ft_strlen(matrix[row]);
		if (row == 0 || row == ((map_data -> total_rows) - 1))
			while (col < line_length)
			{
				if (matrix[row][col] != '1')
					return (false);
				col++;
			}
		else
			if (matrix[row][col] != '1' || matrix[row][line_length - 1] != '1')
				return (false);
		col = 0;
		row++;
	}
	return (true);
}

int	get_total_rows(t_map *map_data)
{
	size_t	row;
	char	**matrix;

	matrix = map_data -> matrix;
	row = 0;
	while (matrix[row])
		row++;
	return (row);	
}

bool	is_duplicate_items(t_map **map_data, char item)
{
	t_map	*data;

	data = *map_data;
	if (item == 'P')
		data -> player += 1;
	if (item == 'E')
		data -> exit += 1;
	if (item == 'C')
		data -> collectibles += 1;
	if (data -> player > 1 || data -> exit > 1)
		return (true);
	return (false);
}

bool	is_valid_fill(t_map **map_data)
{
	size_t	col;
	size_t	row;
	size_t	line_length;
	char	**matrix;

	col = 1;
	row = 0;
	matrix = (*map_data) -> matrix;
	while (matrix[row])
	{
		line_length = ft_strlen(matrix[row]);
		if (row > 0 && row < ((*map_data) -> total_rows - 1))
			while (col < line_length - 1)
			{
				if (!ft_strchr("0PCE1", matrix[row][col]))
					return (false);
				if (is_duplicate_items(map_data, matrix[row][col]))
					return (false);
				col++;
			}
		col = 1;
		row++;
	}
	if ((*map_data) -> collectibles == 0)
		return (false);
	return (true);
}

int	get_position(t_map **map_data, char target)
{
	size_t	col;
	size_t	row;
	size_t	line_length;
	char	**matrix;

	matrix = (*map_data) -> matrix;
	col = 1;
	row = 1;
	while (matrix[row])
	{
		line_length = ft_strlen(matrix[row]);
		while (col < line_length)
		{
			if (matrix[row][col] == target)
			{
				if (target == 'P')
				{
					(*map_data) -> player_pos.x = col;
					(*map_data) -> player_pos.y = row;
					return (1);
				}
				else if (target == 'E')
				{
					(*map_data) -> exit_pos.x = col;
					(*map_data) -> exit_pos.y = row;
					return (1);
				}
			}
			col++;
		}
		col = 1;
		row++;
	}
	return (0);
}

bool	collectibles_visited(Pair collectibles_pos[], int pos_y, int pos_x)
{
	int	i;

	i = 0;
	while (collectibles_pos[i].y != -1)
	{
		if (collectibles_pos[i].y == pos_y && collectibles_pos[i].x == pos_x)
			return (true);
		i++;
	}
	return (false);
}


bool	can_access_collectibles(t_map *map_data, char target)
{
	char	**matrix;
	Pair	queue[(map_data -> total_rows) * (map_data -> line_length)];
	Pair	collectibles_pos[(map_data -> total_rows) * (map_data -> line_length)];
	int		collectibles_index;
	int		front;
	int		tail;
	size_t	player_x;
	size_t	player_y;
	size_t	last_cols;
	size_t	last_rows;
	int		case_stop;


	last_cols = map_data -> line_length;
	last_rows = map_data -> total_rows;
	matrix = map_data -> matrix;
	front = 0;
	tail = 0;
	collectibles_index = 0;
	queue[tail++] = (Pair) {map_data -> player_pos.y, map_data -> player_pos.x};
	case_stop = map_data -> collectibles;
	printf("=================start collectibles===================: %d\n", case_stop);
	for (size_t i = 0; i <(map_data -> total_rows) * (map_data -> line_length); i++)
	{
		collectibles_pos[i].y = -1;
		collectibles_pos[i].x = -1;
	}
	while (front < tail && case_stop)
	{
		Pair	curr_pos = queue[front++];
		player_x = curr_pos.x;
		player_y = curr_pos.y;
		if (player_y + 1 < last_rows && (matrix[player_y + 1][player_x] == target || matrix[player_y + 1][player_x] == '0'))
		{
			queue[tail++] = (Pair) {player_y + 1, player_x};
			if (matrix[player_y + 1][player_x] == target && !collectibles_visited(collectibles_pos, player_y + 1, player_x))
			{
				collectibles_pos[collectibles_index++] = (Pair) {player_y + 1, player_x};
				case_stop--;
			}
		}	
		if (player_y - 1 >= 0 && (matrix[player_y - 1][player_x] == target || matrix[player_y - 1][player_x] == '0'))
		{
			queue[tail++] = (Pair) {player_y - 1, player_x};
			if (matrix[player_y - 1][player_x] == target && !collectibles_visited(collectibles_pos, player_y - 1, player_x))
			{
				collectibles_pos[collectibles_index++] = (Pair) {player_y - 1, player_x};
				case_stop--;
			}
		}
		if (player_x + 1 < last_cols && (matrix[player_y][player_x + 1] == target || matrix[player_y][player_x + 1] == '0'))
		{
			queue[tail++] = (Pair) {player_y, player_x + 1};
			if (matrix[player_y][player_x + 1] == target && !collectibles_visited(collectibles_pos, player_y, player_x + 1))
			{
				collectibles_pos[collectibles_index++] = (Pair) {player_y, player_x + 1};
				case_stop--;
			}
		}
		if (player_x - 1 >= 0 && (matrix[player_y][player_x - 1] == target || matrix[player_y][player_x - 1 ] == '0'))
		{
			queue[tail++] = (Pair) {player_y, player_x - 1};
			if (matrix[player_y][player_x - 1] == target && !collectibles_visited(collectibles_pos, player_y, player_x - 1))
			{
				collectibles_pos[collectibles_index++] = (Pair) {player_y, player_x - 1};
				case_stop--;
			}
		}
		// if (case_stop == 0)
		// {
		// 	printf("pos y: %zu\n", player_y);
		// 	printf("pos x: %zu\n", player_x);
		// 	printf("item x : %c\n", matrix[player_y][player_x]);
		// 	printf("item x - 1 : %c\n", matrix[player_y][player_x - 1]);
		// 	printf("item x + 1 : %c\n", matrix[player_y][player_x + 1]);
		// }
		printf("collectibles===================: %d\n", case_stop);
	}
	if (case_stop)
		return (false);
	return (true);
}


bool	is_valid_player_path(t_map **map_data)
{
	int		reach_c;
	// int		reach_e;
	int		row;
	int		col;
	char	**matrix;
	size_t	line_length;
	size_t	total_rows;

	matrix = (*map_data) -> matrix;
	row = 1;
	col	= 1;
	if (!get_position(map_data, 'P'))
		return (false);
	line_length = (*map_data) -> line_length;
	total_rows = (*map_data) -> total_rows;
	reach_c = can_access_collectibles(*map_data, 'C');	
	return (true);
}


char	*stringify(char *map_path)
{
	char	*map;
	char	*temp;
	char	*line;
	int		fd;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	if (!line)
		return (0);
	map = ft_strjoin("", "");
	while (line)
	{
		temp = ft_strdup(map);
		free(map);
		map = ft_strjoin(temp, line);
		free(temp);
		free(line);
		line = get_next_line(fd);
	}
	printf("%s", map);
	return (map);
}

int	init_map(t_map	**map_data, char *map_path)
{
	*map_data = malloc(sizeof(t_map));
	if (!*map_data)
		return (0);
	(*map_data) -> matrix = ft_split(stringify(map_path), '\n');
	if (!(*map_data) -> matrix)
		return (free(*map_data), 0);
	(*map_data) -> total_rows = get_total_rows(*map_data);
	(*map_data) -> line_length = ft_strlen((*map_data) -> matrix[0]);
	(*map_data) -> player = 0;
	(*map_data) -> exit = 0;
	(*map_data) -> empty = 0;
	(*map_data) -> wall = 0;
	(*map_data) -> collectibles = 0;
	return (1);
}

void	free_map(t_map	*map_data)
{
	int	i;

	i = 0;
	if (map_data -> matrix)
	{
		while(map_data -> matrix[i])
			free(map_data -> matrix[i++]);
		free(map_data -> matrix);
	}
	free(map_data);	
}

int verify_map(char *map_path)
{
	t_map	*map_data;

	if (!init_map(&map_data, map_path))
		return (0);
	if (!is_map_square(map_data))
		return (printf("INVALID SQUARE\n"), free_map(map_data), 0);
	else
		printf("VALID SQUARE\n");
	if (!is_valid_walls(map_data))
		return (printf("INVALID WALLS\n"), free_map(map_data), 0);
	else
		printf("VALID WALLS\n");
	if (!is_valid_fill(&map_data))
		return (printf("INVALID INFILL\n"), free_map(map_data), 0);
	else
		printf("VALID INFILL\n");
	if (!is_valid_player_path(&map_data))
		return (printf("INVALID PLAYER PATH"), free(map_data), 0);
	else
		printf("VALID PLAYER PATH\n");
	printf("total_lines: %zu\n", map_data -> total_rows);
	return (1);
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;

	if (argc < 2)
		return (0);
	mlx = mlx_init();
	if (!mlx)
		return (0);
	if (!verify_map(argv[1]))
	{
		printf("ERROR VERIFY MAP\n");
		free(mlx);
		return (0);
	}
	mlx_win = mlx_new_window(mlx, 800, 600, "test window");
	mlx_loop(mlx);

	return (0);
}

// verify all lines same LENGTH
	// verify first line and last line are only 1 and first char and last char in all rows are also 1
	// verify in the middle after the first char and the last char there are only /PE1CO/
	// verify that the Player P can access the collectibles and access the Exit E
