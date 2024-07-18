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

int	display_game(t_game *game)
{
	t_data	img;
	t_map	*map_data;
	char	**matrix;
	size_t		x;
	size_t		y;

	map_data = game -> map_data;
	matrix = map_data -> matrix;
	img = game -> img_data;
	x = 0;
	y = 0;
	img.img = mlx_xpm_file_to_image(game -> mlx, WALL_X, &(img.img_width), &(img.img_height));
	while(matrix[y])
	{
		while (matrix[y][x])
		{
			if (matrix[y][x] == '1')
				mlx_put_image_to_window(game -> mlx, game -> mlx_win, img.img, (x * img.img_width), (y * img.img_height));
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}
