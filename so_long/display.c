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


char	*select_rock_img(t_game *game, size_t x, size_t y, char target)
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

char	*select_boat_img(t_game *game, int hit)
{
	int			key_direction;
	static int	hit_count = 0;

	key_direction = game -> img_data.boat_direction;
	if (hit)
		hit_count++;
	if ((key_direction == KEY_UP || key_direction == KEY_UP_ARROW) && game -> img_data.boat_up)
	{
		if (hit && hit_count % 2 == 0 && game -> img_data.boat_up_hit)
			return (game -> img_data.boat_up_hit);
		return (game -> img_data.boat_up);
	}
	else if ((key_direction == KEY_DOWN || key_direction == KEY_DOWN_ARROW) && game -> img_data.boat_down)
	{
		if (hit && hit_count % 2 == 0 && game -> img_data.boat_down_hit)
			return (game -> img_data.boat_down_hit);
		return (game -> img_data.boat_down);
	}
	else if ((key_direction == KEY_LEFT || key_direction == KEY_LEFT_ARROW) && game -> img_data.boat_left)
	{
		if (hit && hit_count % 2 == 0  && game -> img_data.boat_left_hit)
			return (game -> img_data.boat_left_hit);
		return (game -> img_data.boat_left);
	}
	else if ((key_direction == KEY_RIGHT || key_direction == KEY_RIGHT_ARROW) && game -> img_data.boat_right)
	{
		if (hit && hit_count % 2 == 0  && game -> img_data.boat_right_hit)
			return (game -> img_data.boat_right_hit);
		return (game -> img_data.boat_right);
	}
	return (game -> img_data.placeholder);
}

int	display_game(t_game *game)
{
	char		**matrix;
	size_t		x;
	size_t		y;
	static int	time_laps = 0;
	static int	hit = 0;

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
				mlx_put_image_to_window(game -> mlx, game -> mlx_win, select_rock_img(game, x, y, '1'), (x * game -> img_data.img_width), (y * game -> img_data.img_height));
			else if (matrix[y][x] == '0' && game -> img_data.sea)
					mlx_put_image_to_window(game -> mlx, game -> mlx_win, game -> img_data.sea, (x * game -> img_data.img_width), (y * game -> img_data.img_height));
			else if (matrix[y][x] == 'P')
				mlx_put_image_to_window(game -> mlx, game -> mlx_win, select_boat_img(game, hit), (x * game -> img_data.img_width), (y * game -> img_data.img_height));
			else if (matrix[y][x] == 'C')
				mlx_put_image_to_window(game -> mlx, game -> mlx_win, game -> img_data.fish_img[1], (x * game -> img_data.img_width), (y * game -> img_data.img_height));
			else if (matrix[y][x] == 'E')
				mlx_put_image_to_window(game -> mlx, game -> mlx_win, game -> img_data.exit_img, (x * game -> img_data.img_width), (y * game -> img_data.img_height));
			x++;
		}
		y++;
	}
	if (game -> start && time_laps > 150 && can_move(game, game -> img_data.boat_direction))
	{
		execute_move(game, game -> img_data.boat_direction);
		time_laps = 0;
		hit = 0;
	}	
	else if (game -> start && time_laps > 200 && !can_move(game, game -> img_data.boat_direction))
		hit++;
	if (hit > 150)
	{
		ft_putendl_fd("YOUR BOAT SINK, TRY AGAIN!", 1);
		free_game(game);
	}
	time_laps++;
	return (0);
}
