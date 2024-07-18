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

int	init_game(t_game **game)
{
	*game = malloc (sizeof (t_game));
	if (!*game)
		return (-1);
	(*game) -> mlx = NULL;
	(*game) -> mlx_win = NULL;
	(*game) -> screen_width = 0;
	(*game) -> screen_height = 0;
	return (0);
}

int	init_map(t_game	**game, char *map_path)
{
	t_map *map_data;

	(*game) -> map_data = malloc(sizeof(t_map));
	if (!(*game) -> map_data)
		return (0);
	map_data = (*game) -> map_data;
	map_data-> matrix = ft_split(stringify(map_path), '\n');
	if (!map_data-> matrix)
		return (free(map_data), 0);
	map_data-> total_rows = get_total_rows(map_data);
	map_data-> total_cols = ft_strlen(map_data-> matrix[0]);
	map_data-> total_cells = (map_data-> total_rows) * (map_data-> total_cols);
	map_data-> player = 0;
	map_data-> exit = 0;
	map_data-> empty = 0;
	map_data-> wall = 0;
	map_data-> collectibles = 0;
	map_data-> reached_items = 0;
	return (1);
}

void	init_queue(t_map *map_data, Pair queue[])
{
	size_t	i;

	i = 0;
	while (i < map_data -> total_cells)
		queue[i++].visited = -1;
	queue[0] = (Pair) {map_data -> player_pos.x, map_data -> player_pos.y, 1};	
}
