/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 04:12:35 by ssghioua          #+#    #+#             */
/*   Updated: 2024/11/22 04:12:36 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	init_shared_mutex(t_params *params)
{
	int	error;

	error = 0;
	if (pthread_mutex_init(&params->write_lock, NULL) != 0)
	{
		free(params);
		error = 1;
	}
	if (!error && pthread_mutex_init(&params->meals_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&params->write_lock);
		free(params);
	}
	if (!error && pthread_mutex_init(&params->display_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&params->write_lock);
		pthread_mutex_destroy(&params->meals_lock);
		free(params);
		error = 1;
	}
	if (!error && pthread_mutex_init(&params->exit_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&params->write_lock);
		pthread_mutex_destroy(&params->meals_lock);
		pthread_mutex_destroy(&params->display_lock);
		free(params);
		error = 1;
	}
	if (error == 1)
	{
		printf("Error: shared mutex init\n");
		exit(EXIT_FAILURE);
	}
}

void	init_forks_mutex(t_params *params)
{
	int	i;

	params->fork = malloc(sizeof(pthread_mutex_t) * params->total_philo);
	if (!params->fork)
	{
		clean_mutex(params, 0);
		free(params);
		printf("Error: forks malloc init\n");
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < params->total_philo)
	{
		if (pthread_mutex_init(&params->fork[i], NULL) != 0)
		{
			clean_mutex(params, i);
			printf("Error: forks mutex init\n");
			exit(EXIT_FAILURE);
		}
	}
}

void	clean_mutex(t_params *params, int forks_mutex)
{
	int	i;

	i = -1;
	while (++i < forks_mutex)
		pthread_mutex_destroy(&params->fork[i]);
	pthread_mutex_destroy(&params->write_lock);
	pthread_mutex_destroy(&params->meals_lock);
	pthread_mutex_destroy(&params->display_lock);
	pthread_mutex_destroy(&params->exit_lock);
}
