/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 05:16:24 by ssghioua          #+#    #+#             */
/*   Updated: 2024/08/24 05:16:25 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	handle_map_validation_err(char *name)
{
	const char	*err_array[] = {ERR_MAP_SIZE, ERR_MAP_SHAPE, ERR_MAP_BORDERS,
		ERR_MAP_INFILL, ERR_MAP_ACCESS_ITEMS};
	int			i;

	i = -1;
	while (err_array[++i])
	{
		if (ft_strncmp(err_array[i], name, ft_strlen(err_array[i])) == 0)
		{
			ft_putendl_fd("MAP IS NOT VALID ", 2);
			ft_putendl_fd((char *)err_array[i], 2);
			break ;
		}
	}
}

void	handle_errors(t_game *game, char *name)
{
	ft_putendl_fd_nl("Error\n", 2);
	if (ft_strncmp(ERR_GAME_INIT, name, ft_strlen(ERR_GAME_INIT)) == 0)
		ft_putendl_fd(ERR_GAME_INIT, 2);
	else if (ft_strncmp(ERR_COLLECTIBLES_INIT, name,
			ft_strlen(ERR_COLLECTIBLES_INIT)) == 0)
		ft_putendl_fd(ERR_COLLECTIBLES_INIT, 2);
	else if (ft_strncmp(ERR_MAP_FORMAT, name,
			ft_strlen(ERR_MAP_FORMAT)) == 0)
		ft_putendl_fd(ERR_MAP_FORMAT, 2);
	else if (ft_strncmp(ERR_MAP_NOT_FOUND, name,
			ft_strlen(ERR_MAP_NOT_FOUND)) == 0)
		ft_putendl_fd(ERR_MAP_NOT_FOUND, 2);
	else if (ft_strncmp(ERR_SPRITE_FORMAT, name,
			ft_strlen(ERR_SPRITE_FORMAT)) == 0)
		ft_putendl_fd_nl(ERR_SPRITE_FORMAT, 2);
	else if (ft_strncmp(ERR_MAP_INIT, name, ft_strlen(ERR_MAP_INIT)) == 0)
		ft_putendl_fd(ERR_MAP_INIT, 2);
	else if (ft_strncmp(ERR_IMG_NOT_FOUND, name,
			ft_strlen(ERR_IMG_NOT_FOUND)) == 0)
		ft_putendl_fd(ERR_IMG_NOT_FOUND, 2);
	else if (ft_strncmp(ERR_PLAYER_POS, name, ft_strlen(ERR_PLAYER_POS)) == 0)
		ft_putendl_fd(ERR_PLAYER_POS, 2);
	else
		handle_map_validation_err(name);
	free_game(game);
}
