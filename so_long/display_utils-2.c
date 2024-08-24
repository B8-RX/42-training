/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils-2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 04:25:34 by ssghioua          #+#    #+#             */
/*   Updated: 2024/08/24 04:25:36 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*select_rock_img(t_game *game, size_t x, size_t y, char target)
{
	if (target == '1')
	{
		if (y == 0 && x == 0)
			return (game->img_data.rock_y_top_left);
		else if (y == 0 && x == game->map_data->total_cols - 1)
			return (game->img_data.rock_y_top_right);
		else if (y == 0)
			return (game->img_data.rock_y_top);
		else if (y == game->map_data->total_rows - 1 && x == 0)
			return (game->img_data.rock_y_bottom_left);
		else if (y == game->map_data->total_rows - 1
			&& x == game->map_data->total_cols - 1)
			return (game->img_data.rock_y_bottom_right);
		else if (y == game->map_data->total_rows - 1)
			return (game->img_data.rock_y_bottom);
		else if (x == 0)
			return (game->img_data.rock_x_left);
		else if (x == game->map_data->total_cols - 1)
			return (game->img_data.rock_x_right);
		else if (x > 0 && x < game->map_data->total_cols && y > 0
			&& y < game->map_data->total_rows)
			return (game->img_data.rock_obstacles);
	}
	return (game->img_data.placeholder);
}

void	put_img_to_window(t_game *game, int x, int y, bool coll_left)
{
	if (game->map_data->matrix[y][x] == '1')
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			select_rock_img(game, x, y, '1'), (x * game->img_data.img_width),
			(y * game->img_data.img_height));
	else if (game->map_data->matrix[y][x] == '0' && game->img_data.sea)
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->img_data.sea, (x * game->img_data.img_width),
			(y * game->img_data.img_height));
	else if (game->map_data->matrix[y][x] == 'P')
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			select_boat_img(game, game->map_data->player_hit),
			(x * game->img_data.img_width),
			(y * game->img_data.img_height));
	else if (game->map_data->matrix[y][x] == 'C')
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->img_data.fish_img[1], (x * game->img_data.img_width),
			(y * game->img_data.img_height));
	else if (game->map_data->matrix[y][x] == 'E' && !coll_left)
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->img_data.exit_img, (x * game->img_data.img_width),
			(y * game->img_data.img_height));
	else if (game->map_data->matrix[y][x] == 'E' && coll_left)
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->img_data.sea, (x * game->img_data.img_width),
			(y * game->img_data.img_height));
}
