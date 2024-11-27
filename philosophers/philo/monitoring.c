/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 04:03:57 by ssghioua          #+#    #+#             */
/*   Updated: 2024/11/22 04:03:58 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	log_action(const char *action, t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->write_lock);
	printf("%lld %d %s\n", get_timestamp() - philo->params->timestamp_start,
		philo->id + 1, action);
	pthread_mutex_unlock(&philo->shared->write_lock);
}

bool	monitor_check_stop_cases(t_philo *philo)
{	
	bool		found_stop_case;

	found_stop_case = false;
	if (someone_starve(philo))
		found_stop_case = true;
	else if (all_philo_satiate(philo))
		found_stop_case = true;
	return (found_stop_case);
}

void	*monitor(void *arg)
{
	t_philo_list	*philo_list;
	t_philo_list	*current;
	t_philo			*philo;
	int				pause;

	philo_list = (t_philo_list *)arg;
	if (philo_list->curr_philo->params->total_philo == 1)
		return (NULL);
	if (philo_list->curr_philo->params->total_philo > 100)
		pause = 10;
	else
		pause = 100;
	while (1)
	{
		current = philo_list;
		while (current)
		{
			philo = current->curr_philo;
			if (monitor_check_stop_cases(philo))
				return (NULL);
			current = current->next;
			usleep(pause);
		}
	}
	return (NULL);
}
