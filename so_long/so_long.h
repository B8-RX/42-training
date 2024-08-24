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
# define EXT "ber"
# define ROCK_Y_TOP "./ASSETS/fishing_game/tiles/rock/xpm/rocks_y_top.xpm"
# define ROCK_Y_TOP_LEFT "./ASSETS/fishing_game/tiles/rock/xpm/rocks_y_top_left.xpm"
# define ROCK_Y_TOP_RIGHT "./ASSETS/fishing_game/tiles/rock/xpm/rocks_y_top_right.xpm"
# define ROCK_Y_BOTTOM "./ASSETS/fishing_game/tiles/rock/xpm/rocks_y_bottom.xpm"
# define ROCK_Y_BOTTOM_LEFT "./ASSETS/fishing_game/tiles/rock/xpm/rocks_y_bottom_left.xpm"
# define ROCK_Y_BOTTOM_RIGHT "./ASSETS/fishing_game/tiles/rock/xpm/rocks_y_bottom_right.xpm"
# define ROCK_X_LEFT "./ASSETS/fishing_game/tiles/rock/xpm/rocks_x_left.xpm"
# define ROCK_X_RIGHT "./ASSETS/fishing_game/tiles/rock/xpm/rocks_x_right.xpm"
# define ROCK_OBSTACLES "./ASSETS/fishing_game/tiles/rock/xpm/rock_obstacles.xpm"
# define WATER_1 "./ASSETS/fishing_game/tiles/sea/xpm/water-v1.xpm"
# define BOAT_UP "./ASSETS/fishing_game/sprites/boat_sprites/xpm/boat_up.xpm"
# define BOAT_DOWN "./ASSETS/fishing_game/sprites/boat_sprites/xpm/boat_down.xpm"
# define BOAT_LEFT "./ASSETS/fishing_game/sprites/boat_sprites/xpm/boat_left.xpm"
# define BOAT_RIGHT "./ASSETS/fishing_game/sprites/boat_sprites/xpm/boat_right.xpm"
# define BOAT_UP_HIT "./ASSETS/fishing_game/sprites/boat_sprites/xpm/boat_up_hit.xpm"
# define BOAT_DOWN_HIT "./ASSETS/fishing_game/sprites/boat_sprites/xpm/boat_down_hit.xpm"
# define BOAT_LEFT_HIT "./ASSETS/fishing_game/sprites/boat_sprites/xpm/boat_left_hit.xpm"
# define BOAT_RIGHT_HIT "./ASSETS/fishing_game/sprites/boat_sprites/xpm/boat_right_hit.xpm"
# define PLACEHOLDER "./ASSETS/fishing_game/placeholder.xpm"
# define EXIT "./ASSETS/fishing_game/tiles/exit/xpm/island_exit.xpm"
# define SQUID "./ASSETS/fishing_game/sprites/fish_sprites/xpm/Squid.xpm" 
# define SALMON "./ASSETS/fishing_game/sprites/fish_sprites/xpm/Salmon.xpm"
# define SOLARFISH "./ASSETS/fishing_game/sprites/fish_sprites/xpm/Solarfish.xpm"
# define CLOWNFISH "./ASSETS/fishing_game/sprites/fish_sprites/xpm/Clownfish.xpm"

typedef struct 
{
	size_t	x;
	size_t	y;
	int	visited;
} Pair;

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
} t_img;

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
	Pair	player_pos;
	Pair	exit_pos;
	size_t	total_rows;
	size_t	total_cols;
	size_t	total_cells;
	size_t	reached_items;
	size_t	total_steps;
} t_map;

typedef struct s_game {
	bool	start;
	void	*mlx;
	void	*mlx_win;
	t_map	*map_data;
	t_img	img_data;
	int		screen_width;
	int		screen_height;
	int		time_laps;
} t_game;

int		check_images(t_game *game);
int		check_images_ext(void);
int		verify_map(t_game **game);
int		check_map_size(t_game *game);
bool	is_map_square(t_map *map_data);
bool	is_valid_walls(t_map *map_data);
bool	is_valid_fill(t_map **map_data);

bool	is_valid_player_path(t_map **map_data);
void	init_queue(t_map *map_data, Pair queue[]);
Pair	get_position(t_map **map_data, char target);
bool	can_access_items(t_map *map_data, size_t total_cells, size_t total_items, char target);
bool	check_path(t_map *map_data, Pair queue[], size_t tail, char *direction, char target);
bool	is_visited_cell(Pair queue[], size_t pos_x, size_t pos_y);

bool	is_duplicate(t_map **map_data, char item);
bool	is_visited_cell(Pair queue[], size_t pos_x, size_t pos_y);
bool	is_target_or_path(t_map *map_data, size_t pos_x, size_t pos_y, char target);
void	update_position(size_t *pos_x, size_t *pos_y, char *direction);
int		check_file(char *file_name);

int		get_total_rows(t_map *map_data);
char	*to_string(t_game *game, char *map_path);

int		init_game(t_game **game);
int		init_map(t_game **game, char *map_path);
int		init_images(t_game *game);
void	*create_image(t_game *game, char *img_path);
void	init_rock(t_game *game);
void	init_boat(t_game *game);
int		init_fish_collection(t_game **game);
char	*select_boat_img(t_game *game, int hit_count);
void	put_img_to_window(t_game *game, int x, int y, bool coll_left);

bool	can_move(t_game *game, int keycode);
void	update_matrix(t_game *game, Pair previous_pos);
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

void	display_error_ext(char *ext, char *file);

#endif
