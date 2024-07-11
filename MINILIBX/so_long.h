#ifndef SO_LONG_H
# define SO_LONG_H
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mlx.h>
#include "libft.h"

typedef struct 
{
	size_t	x;
	size_t	y;
	int	visited;
} Pair;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
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
	t_map	*map_data;
	t_data	img_data;

} t_game;

bool	is_map_square(t_map *map_data);
bool	is_valid_walls(t_map *map_data);
int		get_total_rows(t_map *map_data);
bool	is_duplicate_items(t_map **map_data, char item);
bool	is_valid_fill(t_map **map_data);
int		get_position(t_map **map_data, char target);
bool	is_valid_player_path(t_map **map_data);
char	*stringify(char *map_path);
int		init_map(t_game **game, char *map_path);
void	free_game(t_game *game);
int		verify_map(t_game **game, char *map_path);
bool	can_access_items(t_map *map_data, size_t total_items, char target);
bool	is_target_or_path(t_map *map_data, size_t pos_x, size_t pos_y, char target);
bool	is_visited_cell(Pair queue[], size_t pos_x, size_t pos_y);
bool	check_move(t_map *map_data, Pair queue[], size_t tail, char *direction, char target);
void	update_position(size_t *pos_x, size_t *pos_y, char *direction);


#endif
