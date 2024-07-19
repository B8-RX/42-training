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

	if (argc < 2)
		return (1);
	if (check_extension(argv[1])== -1)
	{
		ft_putendl_fd("ERROR EXTENSION", 2);
		exit(1);
	}
	if (init_game(&game) == -1)
	{
		ft_putendl_fd("ERROR GAME INITIALIZATION", 2);
		exit (1);
	}
	game -> mlx = mlx_init();
	if (!game -> mlx)
	{
		ft_putendl_fd("ERROR SERVER INITIALIZATION", 2);
		free(game);
		exit(1);
	}
	mlx_get_screen_size(game -> mlx, &(game -> screen_width), &(game -> screen_height));
	printf("SCREEN WIDTH = %d\nSCREEN HEIGHT = %d\n", game -> screen_width, game -> screen_height);
	if (verify_map(&game, argv[1]) == -1)
	{
		mlx_destroy_display(game -> mlx);
		free(game -> mlx);
		free_map(game -> map_data);
		free(game);
		exit(1);
	}
	game -> mlx_win = mlx_new_window(game -> mlx, game -> map_data -> total_cols * 128, game -> map_data -> total_rows * 128, "test window");
	if (!game -> mlx_win)
	{
		ft_putendl_fd("ERROR WINDOW INITIALIZATION", 2);
		mlx_destroy_display(game -> mlx);
		free(game -> mlx);
		free_map(game -> map_data);
		free(game);
		exit(1);
	}
	init_images(game);
	mlx_loop_hook(game -> mlx, &display_game, game);
	mlx_key_hook(game -> mlx_win, &key_events, game);
	mlx_hook(game -> mlx_win, 17, 0, &on_destroy, game);
	mlx_loop(game -> mlx);
	on_destroy(game);
	return (0);
}
