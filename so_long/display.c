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
	size_t	x;
	size_t	y;

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
				if (game -> img_data.wall && ((y == 0 || y == game -> map_data -> total_rows -1)|| (x == 0 || x == game -> map_data -> total_cols - 1)))
					mlx_put_image_to_window(game -> mlx, game -> mlx_win, game -> img_data.wall, (x * game -> img_data.img_width), (y * game -> img_data.img_height));
				else
					mlx_put_image_to_window(game -> mlx, game -> mlx_win, game -> img_data.rock, (x * game -> img_data.img_width), (y * game -> img_data.img_height));
					
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
			else if (matrix[y][x] == 'C')
			{
					if (y < 3 || (y > 6 && x > 10))
						mlx_put_image_to_window(game -> mlx, game -> mlx_win, game -> img_data.fish[0], (x * game -> img_data.img_width), (y * game -> img_data.img_height));
					else if (y < 6 && x > 8)
						mlx_put_image_to_window(game -> mlx, game -> mlx_win, game -> img_data.fish[1], (x * game -> img_data.img_width), (y * game -> img_data.img_height));
					else if (y < 6)
						mlx_put_image_to_window(game -> mlx, game -> mlx_win, game -> img_data.fish[2], (x * game -> img_data.img_width), (y * game -> img_data.img_height));
					else if (y > 6)
						mlx_put_image_to_window(game -> mlx, game -> mlx_win, game -> img_data.fish[3], (x * game -> img_data.img_width), (y * game -> img_data.img_height));
			}
			x++;
		}
		y++;
	}
	return (0);
}
