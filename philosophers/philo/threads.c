/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 03:53:27 by ssghioua          #+#    #+#             */
/*   Updated: 2024/11/22 03:53:29 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	create_monitor_thread(t_params *params)
{
	int	total_philo;

	total_philo = params->total_philo;
	if (pthread_create(&params->monitor_thread, NULL, monitor, params->philo_list) != 0)
	{
		clean_mutex(params, total_philo, total_philo);
		clean_data(params);
		fprintf(stderr, "Error on thread creation for monitor\n");
		exit(EXIT_FAILURE);
	}
}

void	create_philo_thread(t_philo *philo, t_params *params)
{
	int	total_philo;

	total_philo = params->total_philo;
	if (pthread_create(&philo->thread,
			NULL, (void *)&routine, philo) != 0)
	{
		clean_mutex(params, total_philo, total_philo);
		clean_data(params);
		fprintf(stderr, "Error on thread creation for philosopher %d\n",
			philo->id);
		exit(EXIT_FAILURE);
	}
}

void	init_wait_threads(t_params *params)
{
	t_philo_list	*current;
	int				total_philo;

	total_philo = params->total_philo;
	current = params->philo_list;
	while (current)
	{
		if (pthread_join(current->curr_philo->thread, NULL) != 0)
		{
			clean_mutex(params, total_philo, total_philo);
			clean_data(params);
			printf("Error: on join thread creation for philo %d\n", current->curr_philo->id + 1);
			exit(EXIT_FAILURE);
		}
		current = current->next;
	}
	if (pthread_join(params->monitor_thread, NULL) != 0)
	{
		clean_mutex(params, total_philo, total_philo);
		clean_data(params);
		printf("Error: on thread creation for monitor\n");
		exit(EXIT_FAILURE);
	}
	if (all_are_ready(params))
	{
		pthread_mutex_lock(&params->ready_lock);
		params->ready = true;
		pthread_mutex_unlock(&params->ready_lock);
	}
}

bool	all_are_ready(t_params *params)
{
	int				total;
	t_philo_list	*current;

	total = 0;
	current = params->philo_list;
	while (current)
	{
		total++;
		current = current->next;
	}
	return (total == params->total_philo);
}
