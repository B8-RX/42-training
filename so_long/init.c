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
	(*game) -> img_data.boat_direction = KEY_UP;
	init_fish_collection(game);
	return (SUCCESS);
}

void	init_fish_collection(t_game **game)
{
	int		i;
	const static char *fish_paths[4] = {
		"./ASSETS/fishing_game/sprites/fish_sprites/xpm/Squid.xpm",
		"./ASSETS/fishing_game/sprites/fish_sprites/xpm/Salmon.xpm",
		"./ASSETS/fishing_game/sprites/fish_sprites/xpm/Solarfish.xpm",
		"./ASSETS/fishing_game/sprites/fish_sprites/xpm/Clownfish.xpm"
	};
	i = 0;
	while (i < 4)
	{
		(*game) -> img_data.fish_collection[i] = (char *)fish_paths[i];
		(*game ) -> img_data.fish_img[i] = NULL;
		i++;
	}
}

int	init_map(t_game	**game, char *map_path)
{
	t_map *map_data;

	(*game) -> map_data = malloc(sizeof(t_map));
	if (!(*game) -> map_data)
		return (ERROR);
	ft_memset((*game) -> map_data, 0, sizeof(t_map));
	map_data = (*game) -> map_data;
	map_data-> matrix = ft_split(stringify(*game, map_path), '\n');
	if (map_data -> str_map)
		free(map_data -> str_map);
	if (!map_data-> matrix)
		return (ERROR);
	map_data-> total_rows = get_total_rows(map_data);
	map_data-> total_cols = ft_strlen(map_data-> matrix[0]);
	map_data-> total_cells = (map_data-> total_rows) * (map_data-> total_cols);
	return (SUCCESS);
}

int	check_img(char *img, char *extension)
{
	if (ft_strncmp(img + (ft_strlen(img) - 3), extension, 3))
	{
		ft_putendl_fd("ERROR EXTENSION SUPPORT ONLY XPM \n", 2);
		return (ERROR);
	}
	return (SUCCESS);
}

void	init_images(t_game *game)
{
	int	i;

	// check_img("xpm");	
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
	i = 0;
	while (i < 4)	
	{
		game -> img_data.fish_img[i] = mlx_xpm_file_to_image(game -> mlx, game -> img_data.fish_collection[i], &(game -> img_data.img_width), &(game -> img_data.img_height));
		i++;
	}
	game -> img_data.placeholder = mlx_xpm_file_to_image(game -> mlx, PLACEHOLDER, &(game -> img_data.img_width), &(game -> img_data.img_height));
	game -> img_data.exit_img = mlx_xpm_file_to_image(game -> mlx, EXIT, &(game -> img_data.img_width), &(game -> img_data.img_height));
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
