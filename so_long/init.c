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

void	init_game(t_game **game)
{
	*game = malloc (sizeof (t_game));
	if (!*game)
		return (handle_errors(*game, ERR_GAME_INIT));
	ft_memset(*game, 0, sizeof(t_game));
	if (init_fish_collection(game) == ERROR)
		return (handle_errors(*game, ERR_COLLECTIBLES_INIT));
	(*game)->start = false;
	return ;
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

void	set_map_infos(t_game *game)
{
	t_map	*data;

	data = game->map_data;
	data->total_rows = get_total_rows(data);
	data->total_cols = ft_strlen(data->matrix[0]);
	data->total_cells = (data->total_rows) * (data->total_cols);
	data->total_steps = 0;
	data->collectibles_left = true;
}

void	init_map(t_game	**game, char *map_path)
{
	t_map	*data;

	(*game)->map_data = ft_calloc(1, sizeof(t_map));
	if (!(*game)->map_data)
		return (handle_errors(*game, "map_init"));
	data = (*game)->map_data;
	if (map_to_string(*game, map_path) == ERROR)
		return (handle_errors(*game, "map_init"));
	data->matrix = ft_split(data->str_map, '\n');
	free(data->str_map);
	if (!data->matrix)
		return (handle_errors(*game, "map_init"));
	set_map_infos(*game);
	return ;
}

void	init_images(t_game *game)
{
	int	i;

	check_images_ext(game);
	init_rock(game);
	init_boat(game);
	game->img_data.sea = create_image(game, WATER_1);
	game->img_data.placeholder = create_image(game, PLACEHOLDER);
	game->img_data.exit_img = create_image(game, EXIT);
	i = -1;
	while (++i < 4)
		game->img_data.fish_img[i] = create_image(game,
				game->img_data.fish_collection[i]);
	check_images(game);
	game->img_data.boat_direction = KEY_LEFT;
	return ;
}
