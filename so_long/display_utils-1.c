/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils-1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 04:21:32 by ssghioua          #+#    #+#             */
/*   Updated: 2024/08/24 04:21:37 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*get_img_boat_up(t_game *game, int hit_count)
{
	if (hit_count && hit_count % 2 == 0 && game->img_data.boat_up_hit)
		return (game->img_data.boat_up_hit);
	return (game->img_data.boat_up);
}

static char	*get_img_boat_down(t_game *game, int hit_count)
{
	if (hit_count && hit_count % 2 == 0 && game->img_data.boat_down_hit)
		return (game->img_data.boat_down_hit);
	return (game->img_data.boat_down);
}

static char	*get_img_boat_left(t_game *game, int hit_count)
{
	if (hit_count && hit_count % 2 == 0 && game->img_data.boat_left_hit)
		return (game->img_data.boat_left_hit);
	return (game->img_data.boat_left);
}

static char	*get_img_boat_right(t_game *game, int hit_count)
{
	if (hit_count && hit_count % 2 == 0 && game->img_data.boat_right_hit)
		return (game->img_data.boat_right_hit);
	return (game->img_data.boat_right);
}

char	*select_boat_img(t_game *game, int hit_count)
{
	int			key_direction;

	key_direction = game->img_data.boat_direction;
	if ((key_direction == KEY_UP || key_direction == KEY_UP_ARROW)
		&& game->img_data.boat_up)
		return (get_img_boat_up(game, hit_count));
	else if ((key_direction == KEY_DOWN || key_direction == KEY_DOWN_ARROW)
		&& game->img_data.boat_down)
		return (get_img_boat_down(game, hit_count));
	else if ((key_direction == KEY_LEFT || key_direction == KEY_LEFT_ARROW)
		&& game->img_data.boat_left)
		return (get_img_boat_left(game, hit_count));
	else if ((key_direction == KEY_RIGHT || key_direction == KEY_RIGHT_ARROW)
		&& game->img_data.boat_right)
		return (get_img_boat_right(game, hit_count));
	return (game->img_data.placeholder);
}
