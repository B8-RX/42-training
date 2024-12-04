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
#include <stdio.h>

bool	all_philo_satiate(t_params *params)
{
	t_philo_list	*list;

	pthread_mutex_lock(&params->satiate_lock);
	list = params->philo_list;
	if (params->max_meals == -1)
	{
		pthread_mutex_unlock(&params->satiate_lock);
		return (false);
	}
	pthread_mutex_lock(&params->meals_lock);
	while(list)
	{
		if (list->curr_philo->meals_eaten < params->max_meals)
		{
			pthread_mutex_unlock(&params->meals_lock);
			pthread_mutex_unlock(&params->satiate_lock);
			return (false);
		}
		list = list->next;
	}
	params->all_finished = true;
	pthread_mutex_unlock(&params->meals_lock);
	pthread_mutex_unlock(&params->satiate_lock);
	return (true);
}

bool	is_philo_starve(t_params *params)
{
	t_philo_list	*list;
	long long		delta;
	
	list = params->philo_list;
	while(list)
	{
		pthread_mutex_lock(&params->philo_list->curr_philo->last_meal_lock);
		delta = get_timestamp() - list->curr_philo->last_meal_timestamp;
		if (delta > params->time_to_die)
		{
			pthread_mutex_unlock(&params->philo_list->curr_philo->last_meal_lock);
			pthread_mutex_lock(&params->dead_lock);
			list->curr_philo->params->a_philo_died = true;
			pthread_mutex_lock(&params->write_lock);
			printf("%lld %d %s\n", get_timestamp() - params->timestamp_start,
				list->curr_philo->id + 1, "died");
			pthread_mutex_unlock(&params->write_lock);
			pthread_mutex_unlock(&params->dead_lock);
			return (true);
		}
		pthread_mutex_unlock(&params->philo_list->curr_philo->last_meal_lock);
		list = list->next;
	}
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
	list->curr_philo->params->a_philo_died = true;
	usleep(list->curr_philo->params->time_to_die * 1000);
	printf("%lld %d %s\n", get_timestamp() - list->curr_philo->params->timestamp_start,
		list->curr_philo->id + 1, "died");
}
