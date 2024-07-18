/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 09:47:05 by ssghioua          #+#    #+#             */
/*   Updated: 2024/07/17 09:47:06 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mlx.h>
#include "libft.h"

# define ESC 65307
# define W 119 
# define A 97
# define S 115
# define D 100
# define EXT "ber"
# define WALL_X "./ASSETS/fishing_game/tiles/sand/xpm/vertopal.com_Sand tiles-horizontal-128x128px.xpm"
# define WALL_X_INDEX 0
# define WALL_Y "./ASSETS/fishing_game/tiles/sand/xpm/vertopal.com_Sand tiles-vertical-128x128px.xpm"
# define WALL_Y_INDEX 1
# define WATER_1 "./ASSETS/fishing_game/tiles/sea/xpm/vertopal.com_water-v1.xpm"
# define WATER_1_INDEX 2
# define WATER_2 "./ASSETS/fishing_game/tiles/sea/xpm/vertopal.com_water-v2.xpm"
# define WATER_2_INDEX 3

typedef struct 
{
	size_t	x;
	size_t	y;
	int	visited;
} Pair;

typedef struct s_data {
	void	*img;
	int		img_width;
	int		img_height;
} t_data;

typedef struct s_map {
	char		**matrix;
	size_t		player;
	size_t		exit;
	Pair		player_pos;
	Pair		exit_pos;
	int			empty;
	int			wall;
	size_t		total_rows;
	size_t		total_cols;
	size_t		total_cells;
	int			collectibles;
	size_t		reached_items;
} t_map;

typedef struct s_game {
	void	*mlx;
	void	*mlx_win;
	t_map	*map_data;
	t_data	img_data;
	int		screen_width;
	int		screen_height;
} t_game;

int		verify_map(t_game **game, char *map_path);
int		check_map_size(t_game *game);
bool	is_map_square(t_map *map_data);
bool	is_valid_walls(t_map *map_data);
bool	is_valid_fill(t_map **map_data);

bool	is_valid_player_path(t_map **map_data);
int		get_position(t_map **map_data, char target);
bool	can_access_items(t_map *map_data, size_t total_items, char target);
bool	check_move(t_map *map_data, Pair queue[], size_t tail, char *direction, char target);
bool	is_visited_cell(Pair queue[], size_t pos_x, size_t pos_y);

bool	is_duplicate_items(t_map **map_data, char item);
bool	is_visited_cell(Pair queue[], size_t pos_x, size_t pos_y);
bool	is_target_or_path(t_map *map_data, size_t pos_x, size_t pos_y, char target);
void	update_position(size_t *pos_x, size_t *pos_y, char *direction);
int		check_extension(char *file_name);


int		get_total_rows(t_map *map_data);
char	*stringify(char *map_path);

int		init_map(t_game **game, char *map_path);
int		init_game(t_game **game);
void	init_queue(t_map *map_data, Pair queue[]);

int		display_game(t_game *game);

void	free_map(t_map *map);
void	free_game(t_game *game);

int		key_events(int keycode, t_game *game);
int		on_key_up(int keycode, t_game *game);
int		on_key_down(int keycode, t_game *game);
int		on_click_down(int button, int x, int y, t_game *game);
int		on_click_up(int button, int x, int y, t_game *game);
int		on_mouse_move(int x, int y, t_game *game);
int		on_destroy(t_game *game);



#endif
