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
		return (-1);
	ft_memset(*game, 0, sizeof(t_game));
	(*game) -> mlx = NULL;
	(*game) -> mlx_win = NULL;
	(*game) -> screen_width = 0;
	(*game) -> screen_height = 0;
	(*game) -> map_data = NULL;
	(*game) -> img_data.img = NULL;
	(*game) -> img_data.wall_x = NULL;
	(*game) -> img_data.wall_y = NULL;
	(*game) -> img_data.sea = NULL;
	(*game) -> img_data.boat_up = NULL;
	(*game) -> img_data.boat_down = NULL;
	(*game) -> img_data.boat_left = NULL;
	(*game) -> img_data.boat_right = NULL;
	(*game) -> img_data.direction = 'd';
	(*game) -> img_data.fish = NULL;
	(*game) -> img_data.exit = NULL;
	(*game) -> img_data.img_width = 0;
	(*game) -> img_data.img_height = 0;
	(*game) -> screen_width = 0;
	(*game) -> screen_height = 0;
	return (0);
}

int	init_map(t_game	**game, char *map_path)
{
	t_map *map_data;

	(*game) -> map_data = malloc(sizeof(t_map));
	if (!(*game) -> map_data)
		return (-1);
	ft_memset((*game) -> map_data, 0, sizeof(t_map));
	map_data = (*game) -> map_data;
	map_data-> matrix = ft_split(stringify(map_path), '\n');
	if (!map_data-> matrix)
		return (free(map_data), 0);
	map_data-> total_rows = get_total_rows(map_data);
	map_data-> total_cols = ft_strlen(map_data-> matrix[0]);
	map_data-> total_cells = (map_data-> total_rows) * (map_data-> total_cols);
	return (0);
}

int	check_img(void *image, int width, int height)
{
	if (image == NULL || width != IMG_SIZE || height != IMG_SIZE)
	{
		ft_putendl_fd("IMAGE CORRUPTED OR NOT CREATED SUCCESSFULLY\n", 2);
		return (-1);
	}
	return (0);
}

void	init_images(t_game *game)
{

	// maybe need to check the extentions of the images ??
	//
	game -> img_data.wall_x = mlx_xpm_file_to_image(game -> mlx, WALL_X, &(game -> img_data.img_width), &(game -> img_data.img_height));
	game -> img_data.wall_y = mlx_xpm_file_to_image(game -> mlx, WALL_Y, &(game -> img_data.img_width), &(game -> img_data.img_height));
	game -> img_data.sea = mlx_xpm_file_to_image(game -> mlx, WATER_1, &(game -> img_data.img_width), &(game -> img_data.img_height));
	game -> img_data.boat_up = mlx_xpm_file_to_image(game -> mlx, BOAT_UP, &(game -> img_data.img_width), &(game -> img_data.img_height));
	game -> img_data.boat_down = mlx_xpm_file_to_image(game -> mlx, BOAT_DOWN, &(game -> img_data.img_width), &(game -> img_data.img_height));
	game -> img_data.boat_left = mlx_xpm_file_to_image(game -> mlx, BOAT_LEFT, &(game -> img_data.img_width), &(game -> img_data.img_height));
	game -> img_data.boat_right = mlx_xpm_file_to_image(game -> mlx, BOAT_RIGHT, &(game -> img_data.img_width), &(game -> img_data.img_height));
}

void	init_queue(t_map *map_data, Pair queue[])
{
	size_t	i;

	i = 0;
	while (i < map_data -> total_cells)
		queue[i++].visited = -1;
	queue[0] = (Pair) {map_data -> player_pos.x, map_data -> player_pos.y, 1};	
}
