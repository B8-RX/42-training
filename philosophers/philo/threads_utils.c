/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 03:53:27 by ssghioua          #+#    #+#             */
/*   Updated: 2024/11/22 03:53:29 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	wait_threads(t_philo_list *philos)
{
	t_philo_list	*current;

	current = philos;
	while (current)
	{
		pthread_join(current->curr_philo->thread, NULL);
		current = current->next;
	}
}

void	create_philos_threads(t_params *params)
{
	t_philo_list	*current;

	current = params->philo_list;
	while (current)
	{
		if (pthread_create(&current->curr_philo->thread,
				NULL, &routine, current->curr_philo) != 0)
		{
			clean_mutex(params, 1);
			clean_data(params);
			fprintf(stderr, "Error on thread creation for philosopher %d\n",
				current->curr_philo->id);
			exit(EXIT_FAILURE);
		}
		current = current->next;
	}
}

int	create_threads(t_params *params)
{
	pthread_t		monitor_thread;
	t_philo_list	*philos;

	philos = params->philo_list;
	create_philos_threads(params);
	if (pthread_create(&monitor_thread, NULL, &monitor, philos) != 0)
	{
		clean_data(params);
		clean_mutex(params, 1);
		fprintf(stderr, "Error on thread creation for monitor\n");
		exit(EXIT_FAILURE);
	}
	wait_threads(params->philo_list);
	pthread_join(monitor_thread, NULL);
	return (0);
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
