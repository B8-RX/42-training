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

t_params	*handle_args(int argc, char **argv)
{
	int			max_meals;
	t_params	*params;

	max_meals = -1;
	if (argc != 5 && argc != 6)
		exit (1);
	if (argc == 6 && argv[5] && is_digits(argv[5]))
		max_meals = ft_atoi(argv[5]);
	params = set_params(argv, max_meals);
	if (!is_valid_args(params, argc, argv))
	{
		free(params);
		exit (1);
	}
	return (params);
}

void	free_philo_list(t_philo_list *list)
{
	t_philo_list	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->curr_philo);
		free(tmp);
	}
}

void	clean_data(t_params *params)
{
	free_philo_list(params->philo_list);
	free(params->fork);
	free(params);
}

void	clean_mutex(t_params *params)
{
	int	i;

	i = -1;
	while (++i < params->total_philo)
		pthread_mutex_destroy(&params->fork[i]);
	pthread_mutex_destroy(&params->write_lock);
	pthread_mutex_destroy(&params->meals_lock);
}
