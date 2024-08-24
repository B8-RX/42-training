/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 09:23:47 by ssghioua          #+#    #+#             */
/*   Updated: 2024/07/17 09:23:49 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_game(t_game **game)
{
	*game = malloc (sizeof (t_game));
	if (!*game)
	{
		ft_putendl_fd("ERROR GAME MEMORY ALLOCATION", 2);
		return (ERROR);
	}
	ft_memset(*game, 0, sizeof(t_game));
	if (init_fish_collection(game) == ERROR)
	{
		free(*game);
		ft_putendl_fd("ERROR FISH INITIALIZATION", 2);
		return (ERROR);
	}
	(*game)->start = false;
	return (SUCCESS);
}

int	init_fish_collection(t_game **game)
{
	int					i;
	const static char	*fish_paths[4] = {
		SQUID,
		SALMON,
		SOLARFISH,
		CLOWNFISH
	};

	if (!*game)
		return (ERROR);
	i = -1;
	while (++i < 4)
	{
		(*game)->img_data.fish_collection[i] = (char *)fish_paths[i];
		(*game)->img_data.fish_img[i] = NULL;
	}
	if ((*game)->img_data.fish_collection[0] == NULL)
		return (ERROR);
	return (SUCCESS);
}

int	init_map(t_game	**game, char *map_path)
{
	t_map	*data;

	(*game)->map_data = malloc(sizeof(t_map));
	if (!(*game)->map_data)
		return (ERROR);
	ft_memset((*game)->map_data, 0, sizeof(t_map));
	data = (*game)->map_data;
	data->str_map = to_string(*game, map_path);
	if (data->str_map == NULL)
		return (ERROR);
	data->matrix = ft_split(data->str_map, '\n');
	if (data->str_map)
		free(data->str_map);
	if (!data->matrix)
		return (ERROR);
	data->total_rows = get_total_rows(data);
	data->total_cols = ft_strlen(data->matrix[0]);
	data->total_cells = (data->total_rows) * (data->total_cols);
	data->total_steps = 0;
	data->collectibles_left = true;
	return (SUCCESS);
}

int	init_images(t_game *game)
{
	int	i;

	if (check_images_ext() == ERROR)
		return (ERROR);
	init_rock(game);
	init_boat(game);
	game->img_data.sea = create_image(game, WATER_1);
	game->img_data.placeholder = create_image(game, PLACEHOLDER);
	game->img_data.exit_img = create_image(game, EXIT);
	i = -1;
	while (++i < 4)
		game->img_data.fish_img[i] = create_image(game,
				game->img_data.fish_collection[i]);
	if (check_images(game) == ERROR)
		return (ERROR);
	game->img_data.boat_direction = KEY_LEFT;
	return (SUCCESS);
}
