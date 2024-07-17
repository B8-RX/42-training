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

int	draw_walls(t_game **game)
{
	t_data	img;
	t_map	*map_data;
	char	**matrix;
	size_t	offset_x;
	size_t	offset_y;
	size_t		x;
	size_t		y;

	map_data = (*game) -> map_data;
	matrix = map_data -> matrix;
	img = (*game) -> img_data;
	x = 0;
	y = 0;
	img.img = mlx_xpm_file_to_image((*game) -> mlx, WALL_X, &(img.img_width), &(img.img_height));
	offset_x = ((*game) -> win_width - ((*game) -> map_data -> line_length * img.img_width)) / 2;
	offset_y = ((*game) -> win_height - ((*game) -> map_data -> total_rows * img.img_height)) / 2;
	while(((y * img.img_height) + offset_y) >= 0 && ((y * img.img_height) + offset_y) < ((map_data -> total_rows * img.img_height) + offset_y))
	{
		while (((x * img.img_width) + offset_x) >= 0 && ((x * img.img_width) + offset_x) < ((map_data -> line_length * img.img_width) + offset_x))
		{
			if (matrix[y][x] == '1')
				mlx_put_image_to_window((*game) -> mlx, (*game) -> mlx_win, img.img, offset_x + (x * img.img_width), offset_y + (y * img.img_height));
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}
