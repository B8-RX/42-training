/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 04:47:30 by ssghioua          #+#    #+#             */
/*   Updated: 2024/08/24 04:47:32 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

bool	can_move(t_game *game, int keycode)
{
	char	**matrix;
	t_pair	pos;
	bool	can_move;

	pos = game->map_data->player_pos;
	matrix = game->map_data->matrix;
	can_move = false;
	if (keycode == KEY_UP || keycode == KEY_UP_ARROW)
		if (pos.y > 0 && (ft_strchr("0CE", matrix[pos.y - 1][pos.x])))
			can_move = true;
	if (keycode == KEY_DOWN || keycode == KEY_DOWN_ARROW)
		if (pos.y < game->map_data->total_rows - 1
			&& (ft_strchr("0CE", matrix[pos.y + 1][pos.x])))
			can_move = true;
	if (keycode == KEY_LEFT || keycode == KEY_LEFT_ARROW)
		if (pos.x > 0 && (ft_strchr("0CE", matrix[pos.y][pos.x - 1])))
			can_move = true;
	if (keycode == KEY_RIGHT || keycode == KEY_RIGHT_ARROW)
		if (pos.x < game->map_data->total_cols - 1
			&& (ft_strchr("0CE", matrix[pos.y][pos.x + 1])))
			can_move = true;
	return (can_move);
}

void	update_matrix(t_game *game, t_pair previous_pos)
{
	size_t	pos_x;
	size_t	pos_y;
	t_map	*data;

	data = game->map_data;
	pos_x = data->player_pos.x;
	pos_y = data->player_pos.y;
	if (data->matrix[pos_y][pos_x] == 'C')
		data->collected += 1;
	else if (data->matrix[pos_y][pos_x] == 'E' && !data->collectibles_left)
		handle_win(game);
	if (data->matrix[pos_y][pos_x] != 'P')
	{
		if (data->matrix[pos_y][pos_x] == 'E')
			data->matrix[previous_pos.y][previous_pos.x] = 'E';
		else
			data->matrix[previous_pos.y][previous_pos.x] = '0';
		data->matrix[pos_y][pos_x] = 'P';
	}
	data->collectibles_left = data->collected < data->collectibles;
}

void	execute_move(t_game *game, int keycode)
{
	t_pair	previous_pos;
	size_t	player_pos_x;
	size_t	player_pos_y;

	player_pos_x = game->map_data->player_pos.x;
	player_pos_y = game->map_data->player_pos.y;
	previous_pos = (t_pair){player_pos_x, player_pos_y, -1};
	if (keycode == KEY_UP || keycode == KEY_UP_ARROW)
		game->map_data->player_pos.y -= 1;
	else if (keycode == KEY_DOWN || keycode == KEY_DOWN_ARROW)
		game->map_data->player_pos.y += 1;
	else if (keycode == KEY_LEFT || keycode == KEY_LEFT_ARROW)
		game->map_data->player_pos.x -= 1;
	else if (keycode == KEY_RIGHT || keycode == KEY_RIGHT_ARROW)
		game->map_data->player_pos.x += 1;
	game->map_data->total_steps++;
	game->time_laps = 0;
	game->map_data->player_hit = 0;
	ft_printf("MOVES: %d\n", game->map_data->total_steps);
	update_matrix(game, previous_pos);
}
