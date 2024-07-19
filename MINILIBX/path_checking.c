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

bool	is_valid_player_path(t_map **map_data)
{
	size_t	total_items;

	if (!get_position(map_data, 'P'))
		return (false);
	total_items = (*map_data) -> collectibles + (*map_data) -> exit;
	if (!can_access_items(*map_data, total_items, 'C'))
		return (false);
	return (true);
}

int	get_position(t_map **map_data, char target)
{
	size_t	col;
	size_t	row;

	col = 1;
	row = 1;
	while (((*map_data) -> matrix)[row])
	{
		while (col < (*map_data) -> total_cols)
		{
			if (((*map_data) -> matrix)[row][col] == target)
			{
				if (target == 'P')
					(*map_data) -> player_pos = (Pair) {col, row, 1};
				else if (target == 'E')
					(*map_data) -> exit_pos = (Pair) {col, row, 1};
				if (target == 'P' || target == 'E')
					return (1);
			}
			col++;
		}
		col = 1;
		row++;
	}
	return (0);
}

bool	can_access_items(t_map *map_data, size_t total_items, char target)
{
	Pair	queue[map_data -> total_cells];
	size_t	front;
	size_t	tail;

	tail = 1;
	front = -1;
	init_queue(map_data, queue);
	while (++front < tail && map_data -> reached_items < total_items)
	{
		map_data -> player_pos = (Pair) {queue[front].x, queue[front].y, -1};
		if (check_path(map_data, queue, tail, "down", target))
			tail++;
		if (check_path(map_data, queue, tail, "up", target))
			tail++;
		if (check_path(map_data, queue, tail, "right", target))
			tail++;
		if (check_path(map_data, queue, tail, "left", target))
			tail++;
	}
	if (map_data -> reached_items < total_items)
		return (false);
	return (true);
}

bool	check_path(t_map *map_data, Pair queue[], size_t tail, char *direction, char target)
{
	size_t	pos_y;	
	size_t	pos_x;
	char	**matrix;
	size_t	border_bottom;
	size_t	border_right;

	pos_y = (map_data -> player_pos).y;
	pos_x = (map_data -> player_pos).x;
	matrix = map_data -> matrix;
	border_bottom = map_data -> total_rows;
	border_right = map_data -> total_cols;
	update_position(&pos_x, &pos_y, direction);
	if (pos_y < border_bottom && pos_y > 0 && pos_x < border_right && pos_x > 0 && is_target_or_path(map_data, pos_x, pos_y, target) && !is_visited_cell(queue, pos_x, pos_y))
	{
		queue[tail] = (Pair) {pos_x, pos_y, 1};
		if (matrix[pos_y][pos_x] == target || matrix[pos_y][pos_x] == 'E') 
			map_data -> reached_items += 1;
		return (true);
	}	
	return (false);
}
