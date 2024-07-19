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
	t_img	img_data;
	char	**matrix;
	size_t		x;
	size_t		y;

	x = 0;
	y = 0;
	if (!game -> mlx_win)
		return (1);
	matrix = game -> map_data -> matrix;
	img_data = game -> img_data;
	while(matrix[y])
	{
		while (matrix[y][x])
		{
			if (matrix[y][x] == '1')
			{
				mlx_put_image_to_window(game -> mlx, game -> mlx_win, img_data.wall, (x * img_data.img_width), (y * img_data.img_height));
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}
