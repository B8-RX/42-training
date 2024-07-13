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
	if ((*map_data) -> collectibles == 0 || (*map_data) -> player != 1 || (*map_data) -> exit != 1)
		return (false);
	return (true);
}

int	get_position(t_map **map_data, char target)
{
	size_t	col;
	size_t	row;

	col = 1;
	row = 1;
	while (((*map_data) -> matrix)[row])
	{
		while (col < (*map_data) -> line_length)
		{
			if (((*map_data) -> matrix)[row][col] == target)
			{
				if (target == 'P')
					(*map_data) -> player_pos = (Pair) {col, row, 1};
				else if (target == 'E')
					(*map_data) -> exit_pos = (Pair) {col, row, 1};
				if (target == 'P' || target == 'E')
					return (1);
			}
			col++;
		}
		col = 1;
		row++;
	}
	return (0);
}

bool	is_visited_cell(Pair queue[], size_t pos_x, size_t pos_y)
{
	int		i;
	int		is_visited;

	i = 0;
	is_visited = 0;
	while (queue[i].visited != -1)
	{
		if ((queue[i].y == pos_y && queue[i].x == pos_x))
		{
			is_visited = 1;
			break;
		}	
		i++;
	}
	if (is_visited)
		return (true);
	return (false);
}

bool	is_target_or_path(t_map	*map_data, size_t pos_x, size_t pos_y, char target)
{
	char	**matrix;
	char	curr_item;

	matrix = map_data -> matrix;
	curr_item = matrix[pos_y][pos_x];
	if (pos_y > 0 && pos_y < (map_data -> total_rows) && pos_x > 0 && pos_x < (map_data -> line_length) && (curr_item == '0' || curr_item == target || curr_item == 'E'))
		return (true);
	return (false);
}

void	update_position(size_t *pos_x, size_t *pos_y, char *direction)
{
	if (ft_strncmp(direction, "down", ft_strlen(direction)) == 0)
		(*pos_y)++;
	else if (ft_strncmp(direction, "up", ft_strlen(direction)) == 0)
		(*pos_y)--;
	else if (ft_strncmp(direction, "right", ft_strlen(direction)) == 0)
		(*pos_x)++;
	else if (ft_strncmp(direction, "left", ft_strlen(direction)) == 0)
		(*pos_x)--;
}

bool	check_move(t_map *map_data, Pair queue[], size_t tail, char *direction, char target)
{
	size_t	pos_y;	
	size_t	pos_x;
	char	**matrix;
	size_t	border_bottom;
	size_t	border_right;

	pos_y = (map_data -> player_pos).y;
	pos_x = (map_data -> player_pos).x;
	matrix = map_data -> matrix;
	border_bottom = map_data -> total_rows;
	border_right = map_data -> line_length;
	update_position(&pos_x, &pos_y, direction);
	if (pos_y < border_bottom && pos_y > 0 && pos_x < border_right && pos_x > 0 && is_target_or_path(map_data, pos_x, pos_y, target) && !is_visited_cell(queue, pos_x, pos_y))
	{
		queue[tail] = (Pair) {pos_x, pos_y, 1};
		if (matrix[pos_y][pos_x] == target || matrix[pos_y][pos_x] == 'E') 
			map_data -> reached_items += 1;
		return (true);
	}	
	return (false);
}

void	init_queue(t_map *map_data, Pair queue[])
{
	size_t	i;

	i = 0;
	while (i < map_data -> total_cells)
		queue[i++].visited = -1;
	queue[0] = (Pair) {map_data -> player_pos.x, map_data -> player_pos.y, 1};	
}

bool	can_access_items(t_map *map_data, size_t total_items, char target)
{
	Pair	queue[map_data -> total_cells];
	size_t	front;
	size_t	tail;

	tail = 1;
	front = -1;
	init_queue(map_data, queue);
	while (++front < tail && map_data -> reached_items < total_items)
	{
		map_data -> player_pos = (Pair) {queue[front].x, queue[front].y, -1};
		if (check_move(map_data, queue, tail, "down", target))
			tail++;
		if (check_move(map_data, queue, tail, "up", target))
			tail++;
		if (check_move(map_data, queue, tail, "right", target))
			tail++;
		if (check_move(map_data, queue, tail, "left", target))
			tail++;
	}
	if (map_data -> reached_items < total_items)
		return (false);
	return (true);
}


bool	is_valid_player_path(t_map **map_data)
{
	int		row;
	int		col;
	char	**matrix;
	size_t	line_length;
	size_t	total_rows;
	size_t	total_items;

	matrix = (*map_data) -> matrix;
	row = 1;
	col	= 1;
	if (!get_position(map_data, 'P'))
		return (false);
	line_length = (*map_data) -> line_length;
	total_rows = (*map_data) -> total_rows;
	total_items = (*map_data) -> collectibles + (*map_data) -> exit;
	if (!can_access_items(*map_data, total_items, 'C'))
		return (false);
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

int	init_map(t_game	**game, char *map_path)
{
	t_map *map_data;

	(*game) -> map_data = malloc(sizeof(t_map));
	if (!(*game) -> map_data)
		return (0);
	map_data = (*game) -> map_data;
	map_data-> matrix = ft_split(stringify(map_path), '\n');
	if (!map_data-> matrix)
		return (free(map_data), 0);
	map_data-> total_rows = get_total_rows(map_data);
	map_data-> line_length = ft_strlen(map_data-> matrix[0]);
	map_data-> total_cells = (map_data-> total_rows) * (map_data-> line_length);
	map_data-> player = 0;
	map_data-> exit = 0;
	map_data-> empty = 0;
	map_data-> wall = 0;
	map_data-> collectibles = 0;
	map_data-> reached_items = 0;
	return (1);
}

void	free_game(t_game *game)
{
	int	i;

	i = 0;
	if (!game)
		return ;
	if (game -> mlx)
		free(game -> mlx);
	if (game -> mlx_win)
		free(game -> mlx_win);
	if (game -> map_data)
	{
		if (game -> map_data -> matrix)
		{
			while(game -> map_data -> matrix[i])
				free(game -> map_data -> matrix[i++]);
			free(game -> map_data -> matrix);
		}
		free(game -> map_data);	
	}
	free(game);
}

int verify_map(t_game **game, char *map_path)
{
	t_map	*map_data;

	if (!init_map(game, map_path))
		return (0);
	map_data = (*game) -> map_data;
	if (!is_map_square(map_data))
		return (printf("INVALID SQUARE\n"), 0);
	else
		printf("VALID SQUARE\n");
	if (!is_valid_walls(map_data))
		return (printf("INVALID WALLS\n"), 0);
	else
		printf("VALID WALLS\n");
	if (!is_valid_fill(&map_data))
		return (printf("INVALID INFILL\n"), 0);
	else
		printf("VALID INFILL\n");
	if (!is_valid_player_path(&map_data))
		return (printf("INVALID PLAYER PATH\n"), 0);
	else
		printf("VALID PLAYER PATH\n");
	printf("total_lines: %zu\n", map_data -> total_rows);
	return (1);
}
 

// int	main(int argc, char **argv)
// {
// 	t_game	*game;
// 	// t_data	img;
//
// 	if (argc < 2)
// 		return (1);
// 	game = malloc (sizeof (t_game));
// 	if (!game)
// 		return (1);
// 	game -> mlx = mlx_init();
// 	if (!game -> mlx)
// 		return (1);
// 	if (!verify_map(&game, argv[1]))
// 	{
// 		printf("ERROR VERIFY MAP\n");
// 		free_game(game);
// 		return (1);
// 	}
// 	game -> mlx_win = mlx_new_window(game -> mlx, 1920, 1080, "test window");
// 	if (!game -> mlx_win)
// 	{
// 		free_game(game);
// 		return (1);
// 	}
// 	// img = game -> img_data;
// 	// img.img = mlx_new_image(game -> mlx, 1920, 1080);
// 	// img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
// 	// my_mlx_pixel_put(&img, 55, 55, 0x00FF0000);
// 	// mlx_put_image_to_window(game -> mlx, game -> mlx_win, img.img, 0, 0);
// 	mlx_loop(game -> mlx);
// 	return (0);
// }
//

void	draw_walls(t_game **game)
{
	t_data	img;
	t_map	*map_data;
	char	**matrix;
	size_t		x;
	size_t		y;

	map_data = (*game) -> map_data;
	matrix = map_data -> matrix;
	img = (*game) -> img_data;
	x = 0;
	y = 0;
	
// check if the map is <= the window . (img size * img in one line) must be <= mlx_new_window
	
	img.img = mlx_xpm_file_to_image((*game) -> mlx, WALL_X, &img.img_width, &img.img_height);
	while(y >= 0 && y < map_data -> total_rows)
	{
		while (x >= 0 && x < map_data -> line_length)
		{
			if (matrix[y][x] == '1')
				mlx_put_image_to_window((*game) -> mlx, (*game) -> mlx_win, img.img, (x * 64), (y * 64));
			x++;
		}
		x = 0;
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_game	*game;
	// t_data	img;

	if (argc < 2)
		return (1);
	game = malloc (sizeof (t_game));
	if (!game)
		return (1);

	game -> mlx = mlx_init();
	if (!game -> mlx)
		return (1);
	game -> win_width = 1920;
	game -> win_height = 1080;
	game -> mlx_win = mlx_new_window(game -> mlx, game -> win_width, game -> win_height, "test window");
	if (!game -> mlx_win)
	{
		free_game(game);
		return (1);
	}
	if (!verify_map(&game, argv[1]))
	{
		printf("ERROR VERIFY MAP\n");
		free_game(game);
		return (1);
	}
 	// img = game -> img_data;
	// img.img = mlx_new_image(game -> mlx, game -> win_width, game -> win_height);
	// img.img_addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	//
	// img.img = mlx_xpm_file_to_image(game -> mlx, WALL_X, &img.img_width, &img.img_height);	
	
	// my_mlx_pixel_put(&img, game -> width, game -> height, 0x00FF0000);
	// draw_square(&img, 55, 55, 0x00FF0000, 200, 200);
	// draw_triangle(&img, 55, 55, 0x00FF0000, 200, 200);
	draw_walls(&game);
	// mlx_put_image_to_window(game -> mlx, game -> mlx_win, img.img, 0, 0);
	mlx_loop(game -> mlx);
	return (0);
}
