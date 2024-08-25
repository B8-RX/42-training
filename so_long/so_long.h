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
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <mlx.h>
# include "libft.h"

# define ERR_GAME_INIT "err_game_init"
# define ERR_COLLECTIBLES_INIT "err_collectibles_init"
# define ERR_MAP_FORMAT "err_map_format"
# define ERR_MAP_NOT_FOUND "err_map_not_found"
# define ERR_PLAYER_POS "player_pos"
# define ERR_SPRITE_FORMAT "sprite_format"
# define ERR_MAP_INIT "map_init"
# define ERR_IMG_NOT_FOUND "img_not_found"
# define ERR_MAP_SIZE "error_size"
# define ERR_MAP_SHAPE "not_square"
# define ERR_MAP_BORDERS "error_borders"
# define ERR_MAP_INFILL "error_infill"
# define ERR_MAP_ACCESS_ITEMS "error_access_items"
# define EXTENSION "xpm"
# define SUCCESS 0
# define ERROR 1
# define IMG_SIZE 128
# define KEY_ESC 65307
# define KEY_LEFT 97
# define KEY_UP 119 
# define KEY_RIGHT 100
# define KEY_DOWN 115
# define KEY_LEFT_ARROW 65361
# define KEY_UP_ARROW 65362 
# define KEY_RIGHT_ARROW 65363
# define KEY_DOWN_ARROW 65364
# define EXT ".ber"
# define ROCK_Y_TOP "./ASSETS/game/tiles/rock/rocks_y_top.xpm"
# define ROCK_Y_TOP_LEFT "./ASSETS/game/tiles/rock/rocks_y_top_left.xpm"
# define ROCK_Y_TOP_RIGHT "./ASSETS/game/tiles/rock/rocks_y_top_right.xpm"
# define ROCK_Y_BOTTOM "./ASSETS/game/tiles/rock/rocks_y_bottom.xpm"
# define ROCK_Y_BOTTOM_LEFT "./ASSETS/game/tiles/rock/rocks_y_bottom_left.xpm"
# define ROCK_Y_BOTTOM_RIGHT "./ASSETS/game/tiles/rock/rocks_y_bottom_right.xpm"
# define ROCK_X_LEFT "./ASSETS/game/tiles/rock/rocks_x_left.xpm"
# define ROCK_X_RIGHT "./ASSETS/game/tiles/rock/rocks_x_right.xpm"
# define ROCK_OBSTACLES "./ASSETS/game/tiles/rock/rock_obstacles.xpm"
# define WATER_1 "./ASSETS/game/tiles/sea/xpm/water-v1.xpm"
# define BOAT_UP "./ASSETS/game/sprites/boat/xpm/boat_up.xpm"
# define BOAT_DOWN "./ASSETS/game/sprites/boat/xpm/boat_down.xpm"
# define BOAT_LEFT "./ASSETS/game/sprites/boat/xpm/boat_left.xpm"
# define BOAT_RIGHT "./ASSETS/game/sprites/boat/xpm/boat_right.xpm"
# define BOAT_UP_HIT "./ASSETS/game/sprites/boat/xpm/boat_up_hit.xpm"
# define BOAT_DOWN_HIT "./ASSETS/game/sprites/boat/xpm/boat_down_hit.xpm"
# define BOAT_LEFT_HIT "./ASSETS/game/sprites/boat/xpm/boat_left_hit.xpm"
# define BOAT_RIGHT_HIT "./ASSETS/game/sprites/boat/xpm/boat_right_hit.xpm"
# define PLACEHOLDER "./ASSETS/game/placeholder.xpm"
# define EXIT "./ASSETS/game/tiles/exit/xpm/island_exit.xpm"
# define SQUID "./ASSETS/game/sprites/fish/xpm/Squid.xpm" 
# define SALMON "./ASSETS/game/sprites/fish/xpm/Salmon.xpm"
# define SOLARFISH "./ASSETS/game/sprites/fish/xpm/Solarfish.xpm"
# define CLOWNFISH "./ASSETS/game/sprites/fish/xpm/Clownfish.xpm"

typedef struct s_pair
{
	size_t	x;
	size_t	y;
	int		visited;
}	t_pair;

typedef struct s_img {
	int		img_width;
	int		img_height;
	void	*rock_y_top;
	void	*rock_y_top_left;
	void	*rock_y_top_right;
	void	*rock_y_bottom;
	void	*rock_y_bottom_left;
	void	*rock_y_bottom_right;
	void	*rock_x_left;
	void	*rock_x_right;
	void	*rock_obstacles;
	void	*sea;
	void	*boat_left;
	void	*boat_up;
	void	*boat_right;
	void	*boat_down;
	void	*boat_left_hit;
	void	*boat_up_hit;
	void	*boat_right_hit;
	void	*boat_down_hit;
	int		boat_direction;
	char	*fish_collection[4];
	void	*fish_img[4];
	void	*exit_img;
	void	*placeholder;
}	t_img;

typedef struct s_map {
	char	**matrix;
	char	*str_map;
	size_t	player;
	int		player_hit;
	size_t	collectibles;
	size_t	collected;
	bool	collectibles_left;
	size_t	exit;
	size_t	empty;
	size_t	wall;
	t_pair	player_pos;
	t_pair	exit_pos;
	size_t	total_rows;
	size_t	total_cols;
	size_t	total_cells;
	size_t	reached_items;
	size_t	total_steps;
}	t_map;

typedef struct s_game {
	bool	start;
	void	*mlx;
	void	*mlx_win;
	t_map	*map_data;
	t_img	img_data;
	int		screen_width;
	int		screen_height;
	int		time_laps;
}	t_game;

void	check_images(t_game *game);

void	check_images_ext(t_game *game);

void	verify_map(t_game **game);
void	check_map_size(t_game *game);
void	is_map_square(t_game *game);
void	is_valid_walls(t_game *game, char **matrix);
void	is_valid_fill(t_game *game, t_map *map_data);
void	is_valid_player_path(t_game *game);

void	init_queue(t_map *map_data, t_pair queue[]);
t_pair	get_position(t_map **map_data, char target);
bool	can_access_items(t_map *map_data, size_t total_cells,
			size_t total_items);
bool	check_path(t_map *map_data, t_pair queue[],
			size_t tail, char *direction);
bool	is_visited_cell(t_pair queue[], size_t pos_x, size_t pos_y);

bool	is_duplicate(t_map **map_data, char item);
bool	is_visited_cell(t_pair queue[], size_t pos_x, size_t pos_y);
bool	is_target_or_path(t_map *map_data, size_t pos_x,
			size_t pos_y, char target);
void	update_position(size_t *pos_x, size_t *pos_y, char *direction);
void	check_file(t_game *game, char *file_name);

int		get_total_rows(t_map *map_data);
int		map_to_string(t_game *game, char *map_path);

void	init_game(t_game **game);
void	init_map(t_game **game, char *map_path);
void	set_map_infos(t_game *game);
void	init_images(t_game *game);
void	*create_image(t_game *game, char *img_path);
void	init_rock(t_game *game);
void	init_boat(t_game *game);
int		init_fish_collection(t_game **game);
char	*select_boat_img(t_game *game, int hit_count);

//mlx
void	init_server(t_game *game);
void	init_window(t_game *game);
void	run_game(t_game *game);
void	put_img_to_window(t_game *game, int x, int y, bool coll_left);

bool	can_move(t_game *game, int keycode);
void	update_matrix(t_game *game, t_pair previous_pos);
void	execute_move(t_game *game, int keycode);
int		display_game(t_game *game);

void	free_map(t_map *map);
void	free_game(t_game *game);
void	free_img_rock(t_game *game);
void	free_img_boat(t_game *game);
void	free_img_sea(t_game *game);
void	free_img_exit(t_game *game);
void	free_img_collectibles(t_game *game);
void	on_destroy(t_game *game);
int		on_close(t_game *game);
void	free_double_array(char **array);

int		key_events(int keycode, t_game *game);
void	handle_gameover(t_game *game);
void	handle_win(t_game *game);
void	handle_errors(t_game *game, char *name);

#endif
