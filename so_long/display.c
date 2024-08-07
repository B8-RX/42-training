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


char *select_img(t_game *game, size_t x, size_t y, char target)
{
	if (target == '1')
	{
		if (y == 0 && x == 0)
			return (game -> img_data.rock_y_top_left);
		else if (y == 0 && x == game -> map_data -> total_cols - 1)
			return (game -> img_data.rock_y_top_right);
		else if (y == 0)
			return (game -> img_data.rock_y_top);
		else if (y == game -> map_data -> total_rows - 1 && x == 0)
			return (game -> img_data.rock_y_bottom_left);
		else if (y == game -> map_data -> total_rows - 1 && x == game -> map_data -> total_cols - 1)
			return (game -> img_data.rock_y_bottom_right);
		else if (y == game -> map_data -> total_rows - 1)
			return (game -> img_data.rock_y_bottom);
		else if (x == 0)
			return (game -> img_data.rock_x_left);
		else if (x == game -> map_data -> total_cols - 1)
			return (game -> img_data.rock_x_right);
		else if (x > 0 && x < game -> map_data -> total_cols && y > 0 && y < game -> map_data -> total_rows)
			return (game -> img_data.rock_obstacles);
	}
	return (game -> img_data.placeholder);
}

int	display_game(t_game *game)
{
	char	**matrix;
	size_t	x;
	size_t	y;

	if (!game || !game -> mlx_win)
		return (1);
	matrix = game -> map_data -> matrix;
	y = 0;
	// printf("PLAYER POS X: %zu\n", get_position(&(game -> map_data), 'P').x);
	// printf("PLAYER POS Y: %zu\n", get_position(&(game -> map_data), 'P').y);
	// printf("COLLECTIBLES: %zu\n", game -> map_data -> collectibles);
	// printf("COLLECTED: %zu\n", game -> map_data -> collected);
	// printf("HANDLE EXIT: %zu\n", game -> map_data -> exit);
	while(y < game -> map_data -> total_rows)
	{
		x = 0;
		while (x < game -> map_data -> total_cols)
		{
			if (matrix[y][x] == '1')
				mlx_put_image_to_window(game -> mlx, game -> mlx_win, select_img(game, x, y, '1'), (x * game -> img_data.img_width), (y * game -> img_data.img_height));
			else if (matrix[y][x] == '0')
			{
				if (game -> img_data.sea)
					mlx_put_image_to_window(game -> mlx, game -> mlx_win, game -> img_data.sea, (x * game -> img_data.img_width), (y * game -> img_data.img_height));
			}
			else if (matrix[y][x] == 'P')
			{
				if (game -> img_data.boat_direction == KEY_UP && game -> img_data.boat_up)
					mlx_put_image_to_window(game -> mlx, game -> mlx_win, game -> img_data.boat_up, (x * game -> img_data.img_width), (y * game -> img_data.img_height));
				else if (game -> img_data.boat_direction == KEY_DOWN && game -> img_data.boat_down)
					mlx_put_image_to_window(game -> mlx, game -> mlx_win, game -> img_data.boat_down, (x * game -> img_data.img_width), (y * game -> img_data.img_height));
				else if (game -> img_data.boat_direction == KEY_LEFT && game -> img_data.boat_left)
					mlx_put_image_to_window(game -> mlx, game -> mlx_win, game -> img_data.boat_left, (x * game -> img_data.img_width), (y * game -> img_data.img_height));
				else if (game -> img_data.boat_direction == KEY_RIGHT && game -> img_data.boat_right)
					mlx_put_image_to_window(game -> mlx, game -> mlx_win, game -> img_data.boat_right, (x * game -> img_data.img_width), (y * game -> img_data.img_height));
			}
			else if (matrix[y][x] == 'C')
			{
				mlx_put_image_to_window(game -> mlx, game -> mlx_win, game -> img_data.fish_img[1], (x * game -> img_data.img_width), (y * game -> img_data.img_height));
			}
			else if (matrix[y][x] == 'E')
				mlx_put_image_to_window(game -> mlx, game -> mlx_win, game -> img_data.exit_img, (x * game -> img_data.img_width), (y * game -> img_data.img_height));

			x++;
		}
		y++;
	}
	return (0);
}
