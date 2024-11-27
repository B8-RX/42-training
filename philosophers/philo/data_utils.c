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

bool	is_valid_args(t_params *params)
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
	if (params->meals_arg && params->max_meals < 0)
		is_valid_args = false;
	return (is_valid_args);
}

t_params	*handle_args(int argc, char **argv)
{
	bool		meals_arg;
	int			max_meals;
	t_params	*params;

	meals_arg = false;
	max_meals = -1;
	if (argc != 5 && argc != 6)
		exit (1);
	if (argc == 6 && argv[5] && is_digits(argv[5]))
	{
		meals_arg = true;
		max_meals = ft_atoi(argv[5]);
	}
	params = set_params(argv, meals_arg, max_meals);
	if (!is_valid_args(params))
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

void	clean_data(t_shared *shared, t_philo_list *philo_list, t_params *params)
{
	free(shared->fork);
	free(shared);
	free_philo_list(philo_list);
	free(params);
}

void	clean_mutex(int forks, t_shared *shared)
{
	int	i;

	i = -1;
	while (++i < forks)
		pthread_mutex_destroy(&shared->fork[i]);
	pthread_mutex_destroy(&shared->write_lock);
	pthread_mutex_destroy(&shared->meals_lock);
}
