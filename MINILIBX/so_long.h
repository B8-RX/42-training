#ifndef SO_LONG_H
# define SO_LONG_H
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mlx.h>
#include "libft.h"

typedef struct 
{
	size_t	y;
	size_t	x;
	int	visited;
} Pair;

typedef struct s_map {
	char		**matrix;
	int			player;
	Pair		player_pos;
	int			exit;
	Pair		exit_pos;
	int			empty;
	int			wall;
	size_t		total_rows;
	size_t		line_length;
	int			collectibles;
} t_map;

bool	is_map_square(t_map *map_data);
bool	is_valid_walls(t_map *map_data);
int		get_total_rows(t_map *map_data);
bool	is_duplicate_items(t_map **map_data, char item);
bool	is_valid_fill(t_map **map_data);
int		get_player_pos(t_map **map_data, char target);
bool	is_valid_player_path(t_map **map_data);
char	*stringify(char *map_path);
int		init_map(t_map	**map_data, char *map_path);
void	free_map(t_map	*map_data);
int		verify_map(char *map_path);

#endif
