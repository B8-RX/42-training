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

void	create_monitor_threads(t_philo_list *list)
{
	pthread_t		monitor_thread;

	if (pthread_create(&monitor_thread, NULL, &monitor, list) != 0)
	{
		fprintf(stderr, "Error on thread creation for monitor\n");
		exit(EXIT_FAILURE);
	}
	pthread_join(monitor_thread, NULL);
}

int	create_philo_thread(t_philo *philo, t_params *params)
{
	if (pthread_create(&philo->thread,
			NULL, (void *)&routine, philo) != 0)
	{
		clean_mutex(params);
		clean_data(params);
		fprintf(stderr, "Error on thread creation for philosopher %d\n",
			philo->id);
		return (1);
	}
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
