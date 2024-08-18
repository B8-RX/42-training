/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 09:23:47 by ssghioua          #+#    #+#             */
/*   Updated: 2024/07/17 09:23:49 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"
#include <stdio.h>

int	init_game(t_game **game)
{
	*game = malloc (sizeof (t_game));
	if (!*game)
	{
		ft_putendl_fd("ERROR GAME MEMORY ALLOCATION", 2);
		return (ERROR);
	}
	ft_memset(*game, 0, sizeof(t_game));
	if (init_fish_collection(game) == ERROR)
	{
		free(*game);
		ft_putendl_fd("ERROR FISH INITIALIZATION", 2);
		return (ERROR);
	}
	(*game) -> start = false;
	return (SUCCESS);
}

int	init_fish_collection(t_game **game)
{
	int		i;
	const static char *fish_paths[4] = {
		SQUID,
		SALMON,
		SOLARFISH,
		CLOWNFISH
	};
	if (!*game)
		return (ERROR);
	i = -1;
	while (++i < 4)
	{
		(*game) -> img_data.fish_collection[i] = (char *)fish_paths[i];
		(*game ) -> img_data.fish_img[i] = NULL;
	}
	if ((*game) -> img_data.fish_collection[0] == NULL)
		return (ERROR);
	return (SUCCESS);
}

int	init_map(t_game	**game, char *map_path)
{
	t_map *map_data;

	(*game) -> map_data = malloc(sizeof(t_map));
	if (!(*game) -> map_data)
		return (ERROR);
	ft_memset((*game) -> map_data, 0, sizeof(t_map));
	map_data = (*game) -> map_data;
	map_data -> str_map = to_string(*game, map_path);
	if (map_data -> str_map == NULL)
		return (ERROR);
	map_data-> matrix = ft_split( map_data -> str_map,'\n');
	if (map_data -> str_map)
		free(map_data -> str_map);
	if (!map_data-> matrix)
		return (ERROR);
	map_data-> total_rows = get_total_rows(map_data);
	map_data-> total_cols = ft_strlen(map_data-> matrix[0]);
	map_data-> total_cells = (map_data-> total_rows) * (map_data-> total_cols);
	return (SUCCESS);
}

int	check_image_extention(char *extension)
{
	int		i;
	char	*img_ext;
	const static char *img[24] = {
		ROCK_Y_TOP, ROCK_Y_BOTTOM, ROCK_Y_TOP_LEFT, ROCK_Y_TOP_RIGHT, ROCK_Y_BOTTOM_LEFT, ROCK_Y_BOTTOM_RIGHT,
		ROCK_X_RIGHT, ROCK_X_LEFT, ROCK_OBSTACLES,
		WATER_1, BOAT_UP, BOAT_DOWN, BOAT_LEFT, BOAT_RIGHT, BOAT_UP_HIT, BOAT_DOWN_HIT, BOAT_RIGHT_HIT, BOAT_LEFT_HIT, PLACEHOLDER, EXIT, SQUID, SALMON, SOLARFISH,CLOWNFISH
	};

	i = -1;
	while (++i < 20)
	{
		img_ext = ft_strdup(img[i] + ft_strlen(img[i])- 3);
		if (ft_strncmp(img_ext, extension, 3))
		{
			ft_putendl_fd_nl("ERROR EXTENSION: SUPPORT ONLY [.xpm] FILE AND GET [.", 2);
			ft_putendl_fd_nl(img_ext, 2);
			ft_putendl_fd("]", 2);
			ft_putendl_fd((char *)img[i], 2);
			free(img_ext);
			return (ERROR);
		}
		free(img_ext);
	}
	return (SUCCESS);
}

void	init_images(t_game *game)
{
	int	i;

	if (check_image_extention("xpm") == ERROR)
		return (free_game(game));
	game -> img_data.rock_y_top = mlx_xpm_file_to_image(game -> mlx, ROCK_Y_TOP, &(game -> img_data.img_width), &(game -> img_data.img_height));
	game -> img_data.rock_y_top_left = mlx_xpm_file_to_image(game -> mlx, ROCK_Y_TOP_LEFT, &(game -> img_data.img_width), &(game -> img_data.img_height));
	game -> img_data.rock_y_top_right = mlx_xpm_file_to_image(game -> mlx, ROCK_Y_TOP_RIGHT, &(game -> img_data.img_width), &(game -> img_data.img_height));
	game -> img_data.rock_y_bottom = mlx_xpm_file_to_image(game -> mlx, ROCK_Y_BOTTOM, &(game -> img_data.img_width), &(game -> img_data.img_height));
	game -> img_data.rock_y_bottom_left = mlx_xpm_file_to_image(game -> mlx, ROCK_Y_BOTTOM_LEFT, &(game -> img_data.img_width), &(game -> img_data.img_height));
	game -> img_data.rock_y_bottom_right = mlx_xpm_file_to_image(game -> mlx, ROCK_Y_BOTTOM_RIGHT, &(game -> img_data.img_width), &(game -> img_data.img_height));
	game -> img_data.rock_x_left = mlx_xpm_file_to_image(game -> mlx, ROCK_X_LEFT, &(game -> img_data.img_width), &(game -> img_data.img_height));
	game -> img_data.rock_x_right = mlx_xpm_file_to_image(game -> mlx, ROCK_X_RIGHT, &(game -> img_data.img_width), &(game -> img_data.img_height));
	game -> img_data.rock_obstacles = mlx_xpm_file_to_image(game -> mlx, ROCK_OBSTACLES, &(game -> img_data.img_width), &(game -> img_data.img_height));
	game -> img_data.sea = mlx_xpm_file_to_image(game -> mlx, WATER_1, &(game -> img_data.img_width), &(game -> img_data.img_height));
	game -> img_data.boat_up = mlx_xpm_file_to_image(game -> mlx, BOAT_UP, &(game -> img_data.img_width), &(game -> img_data.img_height));
	game -> img_data.boat_down = mlx_xpm_file_to_image(game -> mlx, BOAT_DOWN, &(game -> img_data.img_width), &(game -> img_data.img_height));
	game -> img_data.boat_left = mlx_xpm_file_to_image(game -> mlx, BOAT_LEFT, &(game -> img_data.img_width), &(game -> img_data.img_height));
	game -> img_data.boat_right = mlx_xpm_file_to_image(game -> mlx, BOAT_RIGHT, &(game -> img_data.img_width), &(game -> img_data.img_height));
	
	game -> img_data.boat_up_hit = mlx_xpm_file_to_image(game -> mlx, BOAT_UP_HIT, &(game -> img_data.img_width), &(game -> img_data.img_height));
	game -> img_data.boat_down_hit = mlx_xpm_file_to_image(game -> mlx, BOAT_DOWN_HIT, &(game -> img_data.img_width), &(game -> img_data.img_height));
	game -> img_data.boat_left_hit = mlx_xpm_file_to_image(game -> mlx, BOAT_LEFT_HIT, &(game -> img_data.img_width), &(game -> img_data.img_height));
	game -> img_data.boat_right_hit = mlx_xpm_file_to_image(game -> mlx, BOAT_RIGHT_HIT, &(game -> img_data.img_width), &(game -> img_data.img_height));

	game -> img_data.placeholder = mlx_xpm_file_to_image(game -> mlx, PLACEHOLDER, &(game -> img_data.img_width), &(game -> img_data.img_height));
	game -> img_data.exit_img = mlx_xpm_file_to_image(game -> mlx, EXIT, &(game -> img_data.img_width), &(game -> img_data.img_height));
	i = -1;
	while (++i < 4)	
		game -> img_data.fish_img[i] = mlx_xpm_file_to_image(game -> mlx, game -> img_data.fish_collection[i], &(game -> img_data.img_width), &(game -> img_data.img_height));
	game -> img_data.boat_direction = KEY_LEFT;
}

void	init_queue(t_map *map_data, Pair queue[])
{
	size_t	i;

	i = 0;
	if (!map_data)
		return ;
	while (i < map_data -> total_cells)
		queue[i++].visited = -1;
	queue[0] = (Pair) {map_data -> player_pos.x, map_data -> player_pos.y, 1};
}
