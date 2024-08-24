/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 09:32:17 by ssghioua          #+#    #+#             */
/*   Updated: 2024/07/17 09:32:19 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	display_game(t_game *game)
{
	size_t		x;
	size_t		y;

	if (!game || !game->mlx_win)
		return (1);
	y = -1;
	while (++y < game->map_data->total_rows)
	{
		x = -1;
		while (++x < game->map_data->total_cols)
			put_img_to_window(game, x, y, game->map_data->collectibles_left);
	}
	if (game->start && game->time_laps > 100
		&& can_move(game, game->img_data.boat_direction))
		execute_move(game, game->img_data.boat_direction);
	if (game->start && game->time_laps > 200
		&& !can_move(game, game->img_data.boat_direction))
		game->map_data->player_hit++;
	if (game->time_laps > 150 && game->map_data->player_hit > 200)
		handle_gameover(game);
	game->time_laps++;
	return (0);
}
