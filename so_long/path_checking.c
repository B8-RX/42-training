/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checking.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 09:18:18 by ssghioua          #+#    #+#             */
/*   Updated: 2024/07/17 09:18:21 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	init_queue(t_map *map_data, t_pair queue[])
{
	size_t	i;

	i = 0;
	if (!map_data)
		return ;
	while (i < map_data->total_cells)
		queue[i++].visited = -1;
	queue[0] = (t_pair){map_data->player_pos.x, map_data->player_pos.y, 1};
}

void	is_valid_player_path(t_game *game)
{
	size_t	total_items;
	t_map	*map_data;
	t_pair	pos;

	map_data = game->map_data;
	pos = get_position(&map_data, 'P');
	if (pos.y == 0)
		return (handle_errors(game, "player_pos"));
	map_data->player_pos = (t_pair){pos.x, pos.y, -1};
	total_items = map_data->collectibles + map_data->exit;
	if (!can_access_items(map_data, map_data->total_cells, total_items))
		return (handle_errors(game, "error_access_items"));
	return ;
}

t_pair	get_position(t_map **map_data, char target)
{
	size_t	col;
	size_t	row;
	t_pair	position;

	col = 1;
	row = 1;
	position = (t_pair){0, 0, -1};
	while (((*map_data)->matrix)[row])
	{
		while (col < (*map_data)->total_cols)
		{
			if (((*map_data)->matrix)[row][col] == target)
				position = (t_pair){col, row, -1};
			col++;
		}
		col = 1;
		row++;
	}
	return (position);
}

bool	can_access_items(t_map *map_data, size_t cells, size_t total_items)
{
	t_pair	*queue;
	size_t	front;
	size_t	tail;

	free((tail = 1, front = -1, NULL));
	queue = malloc(cells * sizeof(t_pair));
	if (!queue)
		return (false);
	init_queue(map_data, queue);
	while (++front < tail && map_data->reached_items < total_items)
	{
		map_data->player_pos = (t_pair){queue[front].x, queue[front].y, -1};
		if (check_path(map_data, queue, tail, "down"))
			tail++;
		if (check_path(map_data, queue, tail, "up"))
			tail++;
		if (check_path(map_data, queue, tail, "right"))
			tail++;
		if (check_path(map_data, queue, tail, "left"))
			tail++;
	}
	free(queue);
	if (map_data->reached_items < total_items)
		return (false);
	return (true);
}

bool	check_path(t_map *map_data, t_pair queue[], size_t tail, char *side)
{
	size_t	pos_y;	
	size_t	pos_x;
	char	**matrix;
	size_t	border_bottom;
	size_t	border_right;

	matrix = map_data->matrix;
	border_bottom = map_data->total_rows;
	border_right = map_data->total_cols;
	pos_y = (map_data->player_pos).y;
	pos_x = (map_data->player_pos).x;
	update_position(&pos_x, &pos_y, side);
	if (pos_y < border_bottom && pos_y > 0 && pos_x < border_right && pos_x > 0
		&& is_target_or_path(map_data, pos_x, pos_y, 'C')
		&& !is_visited_cell(queue, pos_x, pos_y))
	{
		queue[tail] = (t_pair){pos_x, pos_y, 1};
		if (matrix[pos_y][pos_x] == 'C' || matrix[pos_y][pos_x] == 'E')
			map_data->reached_items += 1;
		return (true);
	}	
	return (false);
}
