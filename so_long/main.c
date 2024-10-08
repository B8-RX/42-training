/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 09:46:37 by ssghioua          #+#    #+#             */
/*   Updated: 2024/07/17 09:46:39 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		return (ft_putstr_fd("Error\nbad arg\n", 2), ERROR);
	game = NULL;
	check_file(game, argv[1]);
	init_game(&game);
	init_server(game);
	init_map(&game, argv[1]);
	verify_map(&game);
	init_window(game);
	init_images(game);
	run_game(game);
	if (game)
		free_game(game);
	return (SUCCESS);
}
