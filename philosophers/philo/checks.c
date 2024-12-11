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

bool	all_philo_satiate(t_philo *philo)
{
	pthread_mutex_lock(&philo->params->meals_lock);
	if (!philo->finished_meals
		&& philo->meals_eaten == philo->params->max_meals)
	{
		pthread_mutex_unlock(&philo->params->meals_lock);
		pthread_mutex_lock(&philo->params->global_lock);
		philo->params->total_philo_finished_meals += 1;
		philo->finished_meals = true;
		if (philo->params->total_philo_finished_meals
			== philo->params->total_philo)
		{
			philo->params->all_finished = true;
			pthread_mutex_unlock(&philo->params->global_lock);
			return (true);
		}
		pthread_mutex_unlock(&philo->params->global_lock);
	}
	else
		pthread_mutex_unlock(&philo->params->meals_lock);
	return (false);
}

bool	is_philo_starve(t_philo *philo)
{
	pthread_mutex_lock(&philo->params->meals_lock);
	if ((get_timestamp() - philo->last_meal_timestamp)
		> philo->params->time_to_die)
	{
		pthread_mutex_unlock(&philo->params->meals_lock);
		pthread_mutex_lock(&philo->params->global_lock);
		philo->params->a_philo_died = true;
		pthread_mutex_lock(&philo->params->display_lock);
		printf("%lld %d died\n",
			get_timestamp() - philo->params->timestamp_start,
			philo->id + 1);
		pthread_mutex_unlock(&philo->params->display_lock);
		pthread_mutex_unlock(&philo->params->global_lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->params->meals_lock);
	return (false);
}

bool	found_stop_cases(t_philo *philo)
{
	bool	stop;

	pthread_mutex_lock(&philo->params->global_lock);
	stop = (philo->params->a_philo_died || philo->params->all_finished);
	pthread_mutex_unlock(&philo->params->global_lock);
	return (stop);
}
