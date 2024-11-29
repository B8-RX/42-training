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

bool	is_philo_satiate(t_philo *philo)
{
	bool	satiate;
	
	satiate = false;
	if (philo->params->meals_arg && !philo->finished_meals)
		satiate = (philo->meals_eaten == philo->params->max_meals);
	return (satiate);
}

bool	is_everybody_satiate(t_philo *philo)
{
	return (philo->params->total_philo_finished_meals == philo->params->total_philo);
}

void	add_philo_satiate(t_philo *philo)
{
	philo->params->total_philo_finished_meals += 1;
	philo->finished_meals = true;
}

bool	all_philo_satiate(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->meals_lock);
	if (is_philo_satiate(philo))
	{
		add_philo_satiate(philo);
		if (is_everybody_satiate(philo))
		{
			pthread_mutex_lock(&philo->shared->end_lock);
			philo->params->all_finished = true;
			pthread_mutex_unlock(&philo->shared->end_lock);
			pthread_mutex_unlock(&philo->shared->meals_lock);
			return (true);
		}
	}
	pthread_mutex_unlock(&philo->shared->meals_lock);
	return (false);
}

bool	is_timeover(t_philo *philo)
{
	bool		is_died;

	is_died = false;
	pthread_mutex_lock(&philo->shared->meals_lock);
	if (philo->last_meal_timestamp > 0)
		is_died = (get_timestamp() - philo->last_meal_timestamp) >= philo->params->time_to_die;
	pthread_mutex_unlock(&philo->shared->meals_lock);
	return (is_died);
}

bool	someone_starve(t_philo *philo)
{
	if (is_timeover(philo))
	{
		pthread_mutex_lock(&philo->shared->end_lock);
		philo->params->a_philo_died = true;
		pthread_mutex_unlock(&philo->shared->end_lock);
		go_die(philo);
		return (true);
	}
	return (false);
}

bool	found_stop_case(t_philo *philo)
{
	bool	stop;

	pthread_mutex_lock(&philo->shared->end_lock);
	stop = philo->params->a_philo_died || philo->params->all_finished;
	pthread_mutex_unlock(&philo->shared->end_lock);
	return (stop);
}

void	handle_single_philo(t_philo_list *list)
{
	log_action("is thinking", list->curr_philo);
	log_action("has taken a fork", list->curr_philo);
	pthread_mutex_lock(&list->curr_philo->shared->end_lock);
	list->curr_philo->params->a_philo_died = true;
	pthread_mutex_unlock(&list->curr_philo->shared->end_lock);
	usleep(list->curr_philo->params->time_to_die * 1000);
	go_die(list->curr_philo);
}
