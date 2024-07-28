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


bool	can_move(t_game *game, char *direction)
{
	char	**matrix;
	Pair	pos;
	bool	can_move;
	size_t	total_fish;
	size_t	catched_fish;
	bool	catch_all_fish;

	total_fish = game -> map_data -> collectibles;
	catched_fish = game -> map_data -> collected;
	catch_all_fish = (total_fish == catched_fish);
	pos = game -> map_data -> player_pos; 
	matrix = game -> map_data -> matrix;
	can_move = false;
	if (ft_strncmp(direction, "up", 2) == 0)
	{
		if (pos.y > 0 && (ft_strchr("0C", matrix[pos.y - 1][pos.x]) || (catch_all_fish && matrix[pos.y - 1][pos.x] == 'E')))
			can_move = true;
	}
	else if (ft_strncmp(direction, "down", 4) == 0)
	{
		if (pos.y < game -> map_data -> total_rows - 1 && (ft_strchr("0C", matrix[pos.y + 1][pos.x]) || (catch_all_fish && matrix[pos.y + 1][pos.x] == 'E')))
			can_move = true;
	}
	else if (ft_strncmp(direction, "left", 4) == 0)
	{
		if (pos.x > 0 && (ft_strchr("0C", matrix[pos.y][pos.x - 1]) || (catch_all_fish && matrix[pos.y][pos.x - 1] == 'E')))
			can_move = true;
	}
	else if (ft_strncmp(direction, "right", 5) == 0)
	{	
		if (pos.x < game -> map_data -> total_cols - 1 && (ft_strchr("0C", matrix[pos.y][pos.x + 1]) || (catch_all_fish && matrix[pos.y][pos.x + 1] == 'E')))
			can_move = true;
	}
	return (can_move);
}

void	execute_action(t_game *game, char *direction)
{
	(void)game;
	printf("CAN HANDLE DIRECTION : %s\n", direction);
}

int	key_events(int keycode, t_game *game)
{
	printf("KEY PRESS: CODE: %d\n", keycode);
	if (keycode == KEY_ESC)
		on_destroy(game);
	else if (keycode == KEY_UP && can_move(game, "up"))
		execute_action(game, "up");
	else if (keycode == KEY_DOWN && can_move(game, "down"))
		execute_action(game, "down");
	else if (keycode == KEY_LEFT && can_move(game, "left"))
		execute_action(game, "left");
	else if (keycode == KEY_RIGHT && can_move(game, "right"))
		execute_action(game, "right");
	return (0);
}

int	on_destroy(t_game *game)
{
	int	i;

	if (game -> img_data.rock_y_top)
		mlx_destroy_image(game, game -> img_data.rock_y_top);
	if (game -> img_data.rock_y_top_left)
		mlx_destroy_image(game, game -> img_data.rock_y_top_left);
	if (game -> img_data.rock_y_top_right)
		mlx_destroy_image(game, game -> img_data.rock_y_top_right);
	if (game -> img_data.rock_y_bottom)
		mlx_destroy_image(game, game -> img_data.rock_y_bottom);
	if (game -> img_data.rock_y_bottom_left)
		mlx_destroy_image(game, game -> img_data.rock_y_bottom_left);
	if (game -> img_data.rock_y_bottom_right)
		mlx_destroy_image(game, game -> img_data.rock_y_bottom_right);
	if (game -> img_data.rock_x_left)
		mlx_destroy_image(game, game -> img_data.rock_x_left);
	if (game -> img_data.rock_x_right)
		mlx_destroy_image(game, game -> img_data.rock_x_right);
	if (game -> img_data.rock_obstacles)
		mlx_destroy_image(game, game -> img_data.rock_obstacles);
	if (game->img_data.sea)
		mlx_destroy_image(game->mlx, game->img_data.sea);
	if (game->img_data.boat_up)
		mlx_destroy_image(game->mlx, game->img_data.boat_up);
	if (game->img_data.boat_down)
		mlx_destroy_image(game->mlx, game->img_data.boat_down);
	if (game->img_data.boat_left)
		mlx_destroy_image(game->mlx, game->img_data.boat_left);
	if (game->img_data.boat_right)
		mlx_destroy_image(game->mlx, game->img_data.boat_right);
	if (game->img_data.placeholder)
		mlx_destroy_image(game->mlx, game->img_data.placeholder);
	if (game->img_data.exit)
		mlx_destroy_image(game->mlx, game->img_data.exit);
	if (*(game->img_data.fish))
	{
		i = 0;
		while (game -> img_data.fish[i])
			mlx_destroy_image(game->mlx, game->img_data.fish[i++]);
	}
	if (game->img_data.exit)
		mlx_destroy_image(game->mlx, game->img_data.exit);
	if (game -> mlx_win)
		mlx_destroy_window(game -> mlx, game -> mlx_win);
	if (game -> mlx)
	{
		mlx_destroy_display(game -> mlx);
		free(game -> mlx);
	}
	free_game(game);
	return (0);
}

// int	on_key_up(int keycode, t_game *game)
// {
// 	printf("key released. KEYCODE: %d\n", keycode);
// 	if (keycode == 65307)
// 		mlx_destroy_window(game -> mlx, game -> mlx_win);
// 	return (0);
// }
//
// int	on_key_down(int keycode, t_game *game)
// {
// 	printf("key pressed. KEYCODE: %d\n", keycode);
// 	(void)game;
// 	return (0);
// }

// int	on_click_down(int button, int x, int y, t_game *game)
// {
// 	printf("click pressed. button: %d\n", button);
// 	printf("x: %d\n", x);
// 	printf("y: %d\n", y);
// 	(void)game;
// 	return (0);
// }
//
// int	on_click_up(int button, int x, int y, t_game *game)
// {
// 	printf("click release button: %d\n", button);
// 	printf("x: %d\n", x);
// 	printf("y: %d\n", y);
// 	(void)game;
// 	return (0);
// }
//
// int	on_mouse_move(int x, int y, t_game *game)
// {
// 	printf("x: %d\n", x);
// 	printf("y: %d\n", y);
// 	(void)game;
// 	return (0);
// }
