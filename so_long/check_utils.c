/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 05:06:56 by ssghioua          #+#    #+#             */
/*   Updated: 2024/08/24 05:06:57 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_images_ext(void)
{
	int					i;
	char				*img_ext;
	const static char	*img[24] = {
		ROCK_Y_TOP, ROCK_Y_BOTTOM, ROCK_Y_TOP_LEFT, ROCK_Y_TOP_RIGHT,
		ROCK_Y_BOTTOM_LEFT, ROCK_Y_BOTTOM_RIGHT,
		ROCK_X_RIGHT, ROCK_X_LEFT, ROCK_OBSTACLES,
		WATER_1, BOAT_UP, BOAT_DOWN, BOAT_LEFT, BOAT_RIGHT, BOAT_UP_HIT,
		BOAT_DOWN_HIT, BOAT_RIGHT_HIT, BOAT_LEFT_HIT, PLACEHOLDER, EXIT,
		SQUID, SALMON, SOLARFISH, CLOWNFISH};

	i = -1;
	while (++i < 20)
	{
		img_ext = ft_strdup(img[i] + ft_strlen(img[i]) - 3);
		if (ft_strncmp(img_ext, EXTENSION, 3))
		{
			display_error_ext(img_ext, (char *)img[i]);
			free(img_ext);
			return (ERROR);
		}
		free(img_ext);
	}
	return (SUCCESS);
}

int	check_images(t_game *game)
{
	t_img	img;

	img = game->img_data;
	if (!img.rock_y_top || !img.rock_x_left || !img.rock_x_right
		|| !img.rock_y_bottom || !img.rock_y_bottom_left
		|| !img.rock_y_bottom_right || !img.rock_x_left
		|| !img.rock_x_right || !img.rock_obstacles
		|| !img.sea || !img.boat_left || !img.boat_up
		|| !img.boat_right || !img.boat_down || !img.boat_left_hit
		|| !img.boat_up_hit || !img.boat_right_hit || !img.boat_down_hit
		|| !img.placeholder || !img.exit_img || !img.fish_img[0]
		|| !img.fish_img[1] || !img.fish_img[2] || !img.fish_img[3])
		return (ft_putendl_fd("IMAGE NOT FOUND", 2), ERROR);
	return (SUCCESS);
}
