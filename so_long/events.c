/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 09:10:19 by ssghioua          #+#    #+#             */
/*   Updated: 2024/07/17 09:10:26 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"


bool	can_move(t_game *game, int keycode)
{
	char	**matrix;
	Pair	pos;
	bool	can_move;
	size_t	total_fish;
	size_t	catched_fish;
	bool	catch_all_fish;

	total_fish = game -> map_data -> collectibles;
	catched_fish = game -> map_data -> collected;
	catch_all_fish = (total_fish == catched_fish);
	pos = game -> map_data -> player_pos; 
	matrix = game -> map_data -> matrix;
	can_move = false;
	if (keycode == KEY_UP)
	{
		if (pos.y > 0 && (ft_strchr("0C", matrix[pos.y - 1][pos.x]) || (catch_all_fish && matrix[pos.y - 1][pos.x] == 'E')))
			can_move = true;
	}
	else if (keycode == KEY_DOWN)
	{
		if (pos.y < game -> map_data -> total_rows - 1 && (ft_strchr("0C", matrix[pos.y + 1][pos.x]) || (catch_all_fish && matrix[pos.y + 1][pos.x] == 'E')))
			can_move = true;
	}
	else if (keycode == KEY_LEFT)
	{
		if (pos.x > 0 && (ft_strchr("0C", matrix[pos.y][pos.x - 1]) || (catch_all_fish && matrix[pos.y][pos.x - 1] == 'E')))
			can_move = true;
	}
	else if (keycode == KEY_RIGHT)
	{	
		if (pos.x < game -> map_data -> total_cols - 1 && (ft_strchr("0C", matrix[pos.y][pos.x + 1]) || (catch_all_fish && matrix[pos.y][pos.x + 1] == 'E')))
			can_move = true;
	}
	return (can_move);
}

void	update_matrix(t_game *game, Pair previous_pos)
{
	size_t	pos_x;
	size_t	pos_y;
	size_t	collectibles;
	char	**matrix;

	matrix = game -> map_data -> matrix;	
	pos_x = game -> map_data -> player_pos.x;
	pos_y = game -> map_data -> player_pos.y;
	collectibles = game -> map_data -> collectibles;
	if (matrix[pos_y][pos_x] == 'C')
		game -> map_data -> collected += 1;
	else if (matrix[pos_y][pos_x] == 'E' && game -> map_data -> collected == collectibles)
	{
		game -> map_data -> exit = 1;
		free_game(game);
	}
	if (matrix[pos_y][pos_x] != 'P')
	{
		matrix[previous_pos.y][previous_pos.x] = '0';
		matrix[pos_y][pos_x] = 'P';
	}
	game -> map_data -> matrix = matrix;
}

void	execute_move(t_game *game, int keycode)
{
	Pair	previous_pos;
	size_t	player_pos_x;
	size_t	player_pos_y;

	player_pos_x = game -> map_data -> player_pos.x;
	player_pos_y = game -> map_data -> player_pos.y;
	previous_pos = (Pair) {player_pos_x, player_pos_y, -1};
	if (keycode == KEY_UP)
		game -> map_data -> player_pos.y -= 1;
	else if (keycode == KEY_DOWN)
		game -> map_data -> player_pos.y += 1;
	else if (keycode == KEY_LEFT)
		game -> map_data -> player_pos.x -= 1;
	else if (keycode == KEY_RIGHT)
		game -> map_data -> player_pos.x += 1;
	update_matrix(game, previous_pos);
}

int	key_events(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		free_game(game);
	game -> img_data.boat_direction = keycode;
	if (can_move(game, keycode))
		execute_move(game, keycode);
	return (0);
}

