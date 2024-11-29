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
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void	set_philos_ready(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->launcher_lock);
	philo->params->philos_ready = true;
	pthread_mutex_unlock(&philo->shared->launcher_lock);
}

int	init_philo_thr(t_philo_list *list, int total_philo)
{
	t_philo_list	*philosophers;
	int				len;

	philosophers = list;
	len = 0;
	while (philosophers)
	{
		len++;
		if (pthread_create(&philosophers->curr_philo->thread,
				NULL, (void *)&routine, philosophers->curr_philo) != 0)
		{
			fprintf(stderr, "Error on thread creation for philosopher %d\n",
				philosophers->curr_philo->id);
			exit(EXIT_FAILURE);
		}
		philosophers = philosophers->next;
	}
	if (len == total_philo)
		set_philos_ready(list->curr_philo);
	return (len);
}

void	create_threads(t_philo_list *list, int total_philo)
{
	t_philo_list	*philosophers;
	pthread_t		monitor_thread;
	int				list_length;

	philosophers = list;
	if (pthread_create(&monitor_thread, NULL, &monitor, list) != 0)
	{
		fprintf(stderr, "Error on thread creation for monitor\n");
		exit(EXIT_FAILURE);
	}
	list_length = init_philo_thr(list, total_philo);
	if (list_length == 1)
		handle_single_philo(list);
	philosophers = list;
	while (philosophers)
	{
		pthread_join(philosophers->curr_philo->thread, NULL);
		philosophers = philosophers->next;
	}
	pthread_join(monitor_thread, NULL);
}

void	init_forks(t_params *params, t_shared *shared)
{
	int	i;

	i = 0;
	while (i < params->total_philo)
	{
		if (pthread_mutex_init(&shared->fork[i], NULL) != 0)
			return (clean_mutex(i, shared));
		i++;
	}
}
