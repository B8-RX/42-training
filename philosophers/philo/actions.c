/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 04:08:38 by ssghioua          #+#    #+#             */
/*   Updated: 2024/11/22 04:08:39 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	go_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->write_lock);
	philo->meals_eaten += 1;
	philo->last_meal_timestamp = get_timestamp();
	pthread_mutex_unlock(&philo->shared->write_lock);
	log_action("is eating", philo);
	usleep(philo->params->time_to_eat * 1000);
}

void	go_sleep(t_philo *philo)
{
	log_action("is sleeping", philo);
	usleep(philo->params->time_to_sleep * 1000);
}

void	go_die(t_philo *philo)
{
	log_action("died", philo);
}

void	handle_single_philo(t_philo_list *list)
{
	log_action("is thinking", list->curr_philo);
	log_action("has taken a fork", list->curr_philo);
	pthread_mutex_lock(&list->curr_philo->shared->write_lock);
	go_die(list->curr_philo);
	list->curr_philo->params->a_philo_died = true;
	pthread_mutex_unlock(&list->curr_philo->shared->write_lock);
}

int	routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->params->total_philo == 1)
		return (1);
	while (1)
	{
		if (found_stop_cases(philo))
			break ;
		log_action("is thinking", philo);
		if (!handle_forks(philo))
			break ;
		go_eat(philo);
		release_forks(philo);
		if (found_stop_cases(philo))
			break ;
		go_sleep(philo);
	}
	return (1);
}