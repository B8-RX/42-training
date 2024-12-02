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
	if (!philo->finished_meals && philo->meals_eaten == philo->params->max_meals)
	{
		philo->params->total_philo_finished_meals += 1;
		philo->finished_meals = true;
		if (philo->params->total_philo_finished_meals == philo->params->total_philo)
		{
			pthread_mutex_lock(&philo->params->satiate_lock);
			philo->params->all_finished = true;
			pthread_mutex_unlock(&philo->params->satiate_lock);
			pthread_mutex_unlock(&philo->params->meals_lock);
			return (true);
		}
	}
	pthread_mutex_unlock(&philo->params->meals_lock);
	return (false);
}

bool	is_philo_starve(t_philo *philo)
{
	long long	delta;

	delta = 0;
	pthread_mutex_lock(&philo->last_meal_lock);
	if (philo->last_meal_timestamp)
		delta = get_timestamp() - philo->last_meal_timestamp;
	pthread_mutex_unlock(&philo->last_meal_lock);
	if (delta >= philo->params->time_to_die)
		return (go_die(philo), true);
	return (false);
}

bool	found_stop_cases(t_philo *philo)
{
	pthread_mutex_lock(&philo->params->satiate_lock);
	if (philo->params->all_finished)
		return (pthread_mutex_unlock(&philo->params->satiate_lock), true);
	pthread_mutex_unlock(&philo->params->satiate_lock);
	pthread_mutex_lock(&philo->params->dead_lock);
	if (philo->params->a_philo_died)
		return (pthread_mutex_unlock(&philo->params->dead_lock), true);
	pthread_mutex_unlock(&philo->params->dead_lock);
	return (false);
}

void	handle_single_philo(t_philo_list *list)
{
	log_action("is thinking", list->curr_philo);
	log_action("has taken a fork", list->curr_philo);
	pthread_mutex_lock(&list->curr_philo->params->write_lock);
	list->curr_philo->params->a_philo_died = true;
	pthread_mutex_unlock(&list->curr_philo->params->write_lock);
	usleep(list->curr_philo->params->time_to_die * 1000);
	go_die(list->curr_philo);
}
