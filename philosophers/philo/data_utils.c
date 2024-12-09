/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 04:18:00 by ssghioua          #+#    #+#             */
/*   Updated: 2024/11/22 04:18:01 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

t_params	*handle_args(int argc, char **argv)
{
	int			max_meals;
	t_params	*params;

	max_meals = -1;
	if (argc != 5 && argc != 6)
		exit (1);
	if (argc == 6 && argv[5] && is_digits(argv[5]))
		max_meals = ft_atoi(argv[5]);
	params = set_data(argv, max_meals);
	if (!is_valid_args(params, argc, argv))
	{
		free(params);
		exit (1);
	}
	return (params);
}

bool	is_valid_args(t_params *params, int argc, char **argv)
{
	bool	is_valid_args;

	is_valid_args = true;
	if (params->total_philo <= 0 || params->total_philo > 200)
		is_valid_args = false;
	if (params->time_to_die < 0)
		is_valid_args = false;
	if (params->time_to_eat < 0)
		is_valid_args = false;
	if (params->time_to_sleep < 0)
		is_valid_args = false;
	if (argc == 6 && ft_atoi(argv[5]) < 0)
		is_valid_args = false;
	return (is_valid_args);
}

t_params	*set_data(char **argv, int max_meals)
{
	t_params	*params;

	params = malloc(sizeof(t_params));
	if (!params)
	{
		fprintf(stderr, "ERROR MEMORY ALLOCATION\n");
		exit (1);
	}
	params->total_philo = ft_atoi(argv[1]);
	params->total_philo_finished_meals = 0;
	params->time_to_die = (long long)ft_atoi(argv[2]);
	params->time_to_eat = (long long)ft_atoi(argv[3]);
	params->time_to_sleep = (long long)ft_atoi(argv[4]);
	params->max_meals = max_meals;
	params->all_finished = false;
	params->a_philo_died = false;
	params->timestamp_start = get_timestamp();
	return (params);
}

void	clean_data(t_params *params)
{
	free_philo_list(params->philo_list);
	free(params->fork);
	free(params);
}
