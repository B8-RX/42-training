/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 05:00:29 by ssghioua          #+#    #+#             */
/*   Updated: 2024/08/24 05:00:31 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_img_rock(t_game *game)
{
	if (game->img_data.rock_y_top)
		mlx_destroy_image(game->mlx, game->img_data.rock_y_top);
	if (game->img_data.rock_y_top_left)
		mlx_destroy_image(game->mlx, game->img_data.rock_y_top_left);
	if (game->img_data.rock_y_top_right)
		mlx_destroy_image(game->mlx, game->img_data.rock_y_top_right);
	if (game->img_data.rock_y_bottom)
		mlx_destroy_image(game->mlx, game->img_data.rock_y_bottom);
	if (game->img_data.rock_y_bottom_left)
		mlx_destroy_image(game->mlx, game->img_data.rock_y_bottom_left);
	if (game->img_data.rock_y_bottom_right)
		mlx_destroy_image(game->mlx, game->img_data.rock_y_bottom_right);
	if (game->img_data.rock_x_left)
		mlx_destroy_image(game->mlx, game->img_data.rock_x_left);
	if (game->img_data.rock_x_right)
		mlx_destroy_image(game->mlx, game->img_data.rock_x_right);
	if (game->img_data.rock_obstacles)
		mlx_destroy_image(game->mlx, game->img_data.rock_obstacles);
}

void	free_img_boat(t_game *game)
{
	if (game->img_data.boat_up)
		mlx_destroy_image(game->mlx, game->img_data.boat_up);
	if (game->img_data.boat_down)
		mlx_destroy_image(game->mlx, game->img_data.boat_down);
	if (game->img_data.boat_left)
		mlx_destroy_image(game->mlx, game->img_data.boat_left);
	if (game->img_data.boat_right)
		mlx_destroy_image(game->mlx, game->img_data.boat_right);
	if (game->img_data.boat_up_hit)
		mlx_destroy_image(game->mlx, game->img_data.boat_up_hit);
	if (game->img_data.boat_down_hit)
		mlx_destroy_image(game->mlx, game->img_data.boat_down_hit);
	if (game->img_data.boat_left_hit)
		mlx_destroy_image(game->mlx, game->img_data.boat_left_hit);
	if (game->img_data.boat_right_hit)
		mlx_destroy_image(game->mlx, game->img_data.boat_right_hit);
}

void	free_img_sea(t_game *game)
{
	if (game->img_data.sea)
		mlx_destroy_image(game->mlx, game->img_data.sea);
}

void	free_img_exit(t_game *game)
{
	if (game->img_data.exit_img)
	{
		mlx_destroy_image(game->mlx, game->img_data.exit_img);
		game->img_data.exit_img = NULL;
	}
}

void	free_img_collectibles(t_game *game)
{
	int	i;

	i = 0;
	if (*(game->img_data.fish_img))
		while (game->img_data.fish_img[i])
			mlx_destroy_image(game->mlx, game->img_data.fish_img[i++]);
}
