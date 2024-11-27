/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 04:01:16 by ssghioua          #+#    #+#             */
/*   Updated: 2024/11/22 04:01:18 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"
#include <pthread.h>

bool	all_philo_satiate(t_philo *philo)
{
	int		total_philo;
	bool	meals_arg;

	total_philo = philo->params->total_philo;
	meals_arg = philo->params->meals_arg;
	pthread_mutex_lock(&philo->shared->write_lock);
	if (meals_arg && philo->meals_eaten == philo->params->max_meals
		&& !philo->finished_meals)
	{
		philo->params->total_philo_finished_meals += 1;
		philo->finished_meals = true;
		if (philo->params->total_philo_finished_meals == total_philo)
		{
			philo->params->all_finished = true;
			pthread_mutex_unlock(&philo->shared->write_lock);
			return (true);
		}
	}
	pthread_mutex_unlock(&philo->shared->write_lock);
	return (false);
}

bool	someone_starve(t_philo *philo)
{
	long long	delta;

	delta = 0;
	pthread_mutex_lock(&philo->shared->meals_lock);
	if (philo->last_meal_timestamp > 0)
		delta = get_timestamp() - philo->last_meal_timestamp;
	pthread_mutex_unlock(&philo->shared->meals_lock);
	if (delta >= philo->params->time_to_die)
	{
		pthread_mutex_lock(&philo->shared->write_lock);
		philo->params->a_philo_died = true;
		pthread_mutex_unlock(&philo->shared->write_lock);
		go_die(philo);
		return (true);
	}
	return (false);
}

bool	found_stop_case(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->write_lock);
	if (philo->params->a_philo_died || philo->params->all_finished)
	{
		pthread_mutex_unlock(&philo->shared->write_lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->shared->write_lock);
	return (false);
}

void	handle_single_philo(t_philo_list *list)
{
	log_action("is thinking", list->curr_philo);
	log_action("has taken a fork", list->curr_philo);
	pthread_mutex_lock(&list->curr_philo->shared->write_lock);
	list->curr_philo->params->a_philo_died = true;
	pthread_mutex_unlock(&list->curr_philo->shared->write_lock);
	usleep(list->curr_philo->params->time_to_die * 1000);
	go_die(list->curr_philo);
}
