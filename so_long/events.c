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

void	handle_win(t_game *game)
{
	game->map_data->exit = 1;
	ft_putendl_fd("CONGRATULATION YOU WIN!", 1);
	free_game(game);
}

void	handle_gameover(t_game *game)
{
	ft_putendl_fd("YOUR BOAT SINK, TRY AGAIN!", 1);
	free_game(game);
}

int	on_close(t_game *game)
{
	free_game(game);
	return (SUCCESS);
}

static bool	is_moving_key(int keycode)
{
	bool	moving_key;

	moving_key = false;
	if (keycode == KEY_LEFT || keycode == KEY_UP
		|| keycode == KEY_RIGHT || keycode == KEY_DOWN
		|| (keycode >= KEY_LEFT_ARROW && keycode <= KEY_DOWN_ARROW))
		moving_key = true;
	return (moving_key);
}

int	key_events(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		return (free_game(game), 0);
	if (is_moving_key(keycode))
	{
		game->img_data.boat_direction = keycode;
		game->start = true;
	}
	if (can_move(game, keycode))
		execute_move(game, keycode);
	return (0);
}
