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

# define IMG_SIZE 128
# define ESC 65307
# define KEY_W 119 
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define EXT "ber"
# define WALL_X "./ASSETS/fishing_game/tiles/sand/xpm/vertopal.com_Sand tiles-horizontal-128x128px.xpm"
# define WALL_Y "./ASSETS/fishing_game/tiles/sand/xpm/vertopal.com_Sand tiles-vertical-128x128px.xpm"
# define WATER_1 "./ASSETS/fishing_game/tiles/sea/xpm/vertopal.com_water-v1.xpm"
# define WATER_2 "./ASSETS/fishing_game/tiles/sea/xpm/vertopal.com_water-v2.xpm"
# define BOAT_UP "./ASSETS/fishing_game/sprites/boat/xpm/vertopal.com_boat_up.xpm"
# define BOAT_DOWN "./ASSETS/fishing_game/sprites/boat/xpm/vertopal.com_boat_down.xpm"
# define BOAT_LEFT "./ASSETS/fishing_game/sprites/boat/xpm/vertopal.com_boat_left.xpm"
# define BOAT_RIGHT "./ASSETS/fishing_game/sprites/boat/xpm/vertopal.com_boat_right.xpm"

typedef struct 
{
	size_t	x;
	size_t	y;
	int	visited;
} Pair;

typedef struct s_img {
	void	*img;
	int		img_width;
	int		img_height;
	void	*wall_x;
	void	*wall_y;
	void	*sea;
	void	*boat_up;
	void	*boat_down;
	void	*boat_left;
	void	*boat_right;
	char	direction;
	void	*fish;
	void	*exit;
} t_img;

typedef struct s_map {
	char	**matrix;
	size_t	player;
	size_t	collectibles;
	size_t	exit;
	size_t	empty;
	size_t	wall;
	Pair	player_pos;
	Pair	exit_pos;
	int		collected;
	int		can_exit;
	size_t	total_rows;
	size_t	total_cols;
	size_t	total_cells;
	size_t	reached_items;
} t_map;

typedef struct s_game {
	void	*mlx;
	void	*mlx_win;
	t_map	*map_data;
	t_img	img_data;
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
bool	check_path(t_map *map_data, Pair queue[], size_t tail, char *direction, char target);
bool	is_visited_cell(Pair queue[], size_t pos_x, size_t pos_y);

bool	is_duplicate_items(t_map **map_data, char item);
bool	is_visited_cell(Pair queue[], size_t pos_x, size_t pos_y);
bool	is_target_or_path(t_map *map_data, size_t pos_x, size_t pos_y, char target);
void	update_position(size_t *pos_x, size_t *pos_y, char *direction);
int		check_extension(char *file_name);


int		get_total_rows(t_map *map_data);
char	*stringify(char *map_path);

void	init_queue(t_map *map_data, Pair queue[]);
int		init_map(t_game **game, char *map_path);
void	init_images(t_game *game);
int		init_game(t_game **game);

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
