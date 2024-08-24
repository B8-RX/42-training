/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 06:18:47 by ssghioua          #+#    #+#             */
/*   Updated: 2024/08/24 06:18:49 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*create_image(t_game *game, char *img_path)
{
	return (mlx_xpm_file_to_image(game->mlx, img_path,
			&game->img_data.img_width, &game->img_data.img_height));
}

void	init_rock(t_game *game)
{
	game->img_data.rock_y_top = create_image(game, ROCK_Y_TOP);
	game->img_data.rock_y_top_left = create_image(game, ROCK_Y_TOP_LEFT);
	game->img_data.rock_y_top_right = create_image(game, ROCK_Y_TOP_RIGHT);
	game->img_data.rock_y_bottom = create_image(game, ROCK_Y_BOTTOM);
	game->img_data.rock_y_bottom_left = create_image(game, ROCK_Y_BOTTOM_LEFT);
	game->img_data.rock_y_bottom_right = create_image(game,
			ROCK_Y_BOTTOM_RIGHT);
	game->img_data.rock_x_left = create_image(game, ROCK_X_LEFT);
	game->img_data.rock_x_right = create_image(game, ROCK_X_RIGHT);
	game->img_data.rock_obstacles = create_image(game, ROCK_OBSTACLES);
}

void	init_boat(t_game *game)
{
	game->img_data.boat_up = create_image(game, BOAT_UP);
	game->img_data.boat_down = create_image(game, BOAT_DOWN);
	game->img_data.boat_left = create_image(game, BOAT_LEFT);
	game->img_data.boat_right = create_image(game, BOAT_RIGHT);
	game->img_data.boat_up_hit = create_image(game, BOAT_UP_HIT);
	game->img_data.boat_down_hit = create_image(game, BOAT_DOWN_HIT);
	game->img_data.boat_left_hit = create_image(game, BOAT_LEFT_HIT);
	game->img_data.boat_right_hit = create_image(game, BOAT_RIGHT_HIT);
}
