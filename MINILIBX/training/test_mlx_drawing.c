#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mlx.h>

# define WALL_X "../ASSETS/TILES/xpm/horizontal_tiles_pacman_v1.xpm"

typedef struct 
{
	size_t	x;
	size_t	y;
	int	visited;
} Pair;

typedef struct s_data {
	void	*img;
	char	*img_addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		img_width;
	int		img_height;
} t_data;

typedef struct s_map {
	char		**matrix;
	size_t		player;
	Pair		player_pos;
	size_t		exit;
	Pair		exit_pos;
	int			empty;
	int			wall;
	size_t		total_rows;
	size_t		line_length;
	size_t		total_cells;
	int			collectibles;
	size_t		reached_items;
} t_map;

typedef struct s_game {
	void	*mlx;
	void	*mlx_win;
	int		win_width;
	int		win_height;
	t_map	*map_data;
	t_data	img_data;

} t_game;

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

void	draw_square(t_data *data, int x_pos, int y_pos, int color, int width, int height)
{
	char	*dst;
	int		x;
	int		y;
	
	x = x_pos;
	y = y_pos;
	while (y < height)
	{
		while (x < width)
		{
			dst = data -> img_addr + (y * data -> line_length + x * (data -> bpp / 8));
			*(unsigned int*)dst = color;
			x++;
		}
		x = x_pos;
		y++;
	}
}

void	draw_triangle(t_data *data, int x_pos, int y_pos, int color, int width, int height)
{
	char	*dst;
	int		x;
	int		y;
	int		row_width;
	int		left_border;
	int		right_border;

	y = y_pos;
	row_width = 1;
	if (x_pos < width / 2)
	{
		x_pos = width;
	}
	while (y < y_pos + height)
	{
		left_border = x_pos - row_width / 2;
		right_border = x_pos + row_width / 2;
		x = left_border;
		while (x <= right_border)
		{
			dst = data -> img_addr + (y * data -> line_length + x * (data -> bpp / 8));
			*(unsigned int*)dst = color;
			x++;
		}
		row_width += 2;
		y++;
	}
}

void	my_mlx_pixel_put(t_data *data, int x_pos, int y_pos, int color)
{
	char	*dst;
	if (x_pos >= 0 && x_pos <= data -> img_width && y_pos >= 0 && y_pos <= data -> img_height)		
	{
		dst = data -> img_addr + (y_pos * data -> line_length + x_pos * (data -> bpp / 8));
		*(unsigned int*)dst = color;
	}	
}

void	draw_walls(t_game **game)
{
	t_data	img;
	t_map	*map_data;
	char	**matrix;
	// int		x;
	// int		y;

	map_data = (*game) -> map_data;
	matrix = map_data -> matrix;
	img = (*game) -> img_data;
	// x = 0;
	// y = 0;
	
// check if the map is <= the window . (img size * img in one line) must be <= mlx_new_window
	
	// while(y >= 0 && y <= map_data -> total_rows)
	// {
	// 	while (x >= 0 && x <= map_data -> line_length)
	// 	{
	img.img = mlx_xpm_file_to_image((*game) -> mlx, WALL_X, &img.img_width, &img.img_height);
	mlx_put_image_to_window((*game) -> mlx, (*game) -> mlx_win, img.img, 0, 0);
	// 		x++;
	// 	}
	// 	x = 0;
	// 	y++;
	// }
}

int	main(int argc, char **argv)
{
	t_game	*game;
	// t_data	img;

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
