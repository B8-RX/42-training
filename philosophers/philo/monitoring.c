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
	pthread_mutex_lock(&philo->params->write_lock);
	printf("%lld %d %s\n", get_timestamp() - philo->params->timestamp_start,
		philo->id + 1, action);
	pthread_mutex_unlock(&philo->params->write_lock);
}

bool	monitor_check_stop_cases(t_philo *philo)
{	
	long long	last_meal_timestamp;
	bool		stop;
	int			meals_arg;

	pthread_mutex_lock(&philo->params->write_lock);
	last_meal_timestamp = philo->last_meal_timestamp;
	meals_arg = philo->params->max_meals;
	pthread_mutex_unlock(&philo->params->write_lock);
	stop = false;
	if (is_philo_starve(philo, last_meal_timestamp))
		stop = true;
	else if (meals_arg != -1 && all_philo_satiate(philo))
		stop = true;
	return (stop);
}

void	*monitor(void *arg)
{
	t_philo_list	*philo_list;
	t_philo_list	*current;
	t_philo			*philo;

	philo_list = (t_philo_list *)arg;
	if (philo_list->curr_philo->params->total_philo == 1)
		return (handle_single_philo(philo_list), NULL);
	while (!all_are_ready(philo_list->curr_philo->params))
		usleep(50);
	while (1)
	{
		current = philo_list;
		while (current)
		{
			philo = current->curr_philo;
			if (monitor_check_stop_cases(philo))
				return (NULL);
			current = current->next;
			usleep(10);
		}
	}
	return (NULL);
}
