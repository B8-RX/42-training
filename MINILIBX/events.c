/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 09:10:19 by ssghioua          #+#    #+#             */
/*   Updated: 2024/07/17 09:10:26 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

int	on_key_up(int keycode, t_game *game)
{
	printf("key released. KEYCODE: %d\n", keycode);
	if (keycode == 65307)
		mlx_destroy_window(game -> mlx, game -> mlx_win);
	return (0);
}

int	on_key_down(int keycode, t_game *game)
{
	printf("key pressed. KEYCODE: %d\n", keycode);
	(void)game;
	return (0);
}

int	on_click_down(int button, int x, int y, t_game *game)
{
	printf("click pressed. button: %d\n", button);
	printf("x: %d\n", x);
	printf("y: %d\n", y);
	(void)game;
	return (0);
}

int	on_click_up(int button, int x, int y, t_game *game)
{
	printf("click release button: %d\n", button);
	printf("x: %d\n", x);
	printf("y: %d\n", y);
	(void)game;
	return (0);
}

int	on_mouse_move(int x, int y, t_game *game)
{
	printf("x: %d\n", x);
	printf("y: %d\n", y);
	(void)game;
	return (0);
}

int	on_destroy(t_game *game)
{
	mlx_destroy_window(game -> mlx, game -> mlx_win);
	return (0);
}
