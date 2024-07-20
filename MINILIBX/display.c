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

#include "./so_long.h"
#include <stdio.h>

int	display_game(t_game *game)
{
	char	**matrix;
	size_t		x;
	size_t		y;

	if (!game || !game -> mlx_win)
		return (1);
	matrix = game -> map_data -> matrix;
	y = 0;
	while(y < game -> map_data -> total_rows)
	{
		x = 0;
		while (x < game -> map_data -> total_cols)
		{
			if (matrix[y][x] == '1')
			{
				if (game -> img_data.wall_x && (y == 0 || y == game -> map_data -> total_rows))
					mlx_put_image_to_window(game -> mlx, game -> mlx_win, game -> img_data.wall_x, (x * game -> img_data.img_width), (y * game -> img_data.img_height));
				else if (game -> img_data.wall_y)	
					mlx_put_image_to_window(game -> mlx, game -> mlx_win, game -> img_data.wall_y, (x * game -> img_data.img_width), (y * game -> img_data.img_height));
			}
			else if (matrix[y][x] == '0')
			{
				if (game -> img_data.sea)
					mlx_put_image_to_window(game -> mlx, game -> mlx_win, game -> img_data.sea, (x * game -> img_data.img_width), (y * game -> img_data.img_height));
			}
			else if (matrix[y][x] == 'P')
			{
				if (game -> img_data.direction == 'u' && game -> img_data.boat_up)
					mlx_put_image_to_window(game -> mlx, game -> mlx_win, game -> img_data.boat_up, (x * game -> img_data.img_width), (y * game -> img_data.img_height));
				else if (game -> img_data.direction == 'd' && game -> img_data.boat_down)
					mlx_put_image_to_window(game -> mlx, game -> mlx_win, game -> img_data.boat_down, (x * game -> img_data.img_width), (y * game -> img_data.img_height));
				else if (game -> img_data.direction == 'l' && game -> img_data.boat_left)
					mlx_put_image_to_window(game -> mlx, game -> mlx_win, game -> img_data.boat_left, (x * game -> img_data.img_width), (y * game -> img_data.img_height));
				else if (game -> img_data.direction == 'r' && game -> img_data.boat_right)
					mlx_put_image_to_window(game -> mlx, game -> mlx_win, game -> img_data.boat_right, (x * game -> img_data.img_width), (y * game -> img_data.img_height));
			}
			x++;
		}
		y++;
	}
	return (0);
}
