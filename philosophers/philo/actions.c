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
#include <pthread.h>
#include <unistd.h>

bool	handle_forks(t_philo *philo)
{
	int	left_fork;
	int	right_fork;
	int	swap;

	left_fork = philo->id;
	right_fork = (philo->id + 1) % philo->params->total_philo;
	if (philo->id % 2 == 0)
	{
		swap = left_fork;
		left_fork = right_fork;
		right_fork = swap;
	}
	if (found_stop_case(philo))
		return (false);
	pthread_mutex_lock(&philo->shared->fork[left_fork]);
	pthread_mutex_lock(&philo->shared->fork[right_fork]);
	if (found_stop_case(philo))
	{
		pthread_mutex_unlock(&philo->shared->fork[right_fork]);
		pthread_mutex_unlock(&philo->shared->fork[left_fork]);
		return (false);
	}
	log_action("has taken a fork", philo);
	log_action("has taken a fork", philo);
	return (true);
}

int	routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->params->total_philo == 1)
		return (1);
	while (1)
	{
		if (found_stop_case(philo))
			break ;
		log_action("is thinking", philo);
		if (!handle_forks(philo))
			break ;
		go_eat(philo);
		release_forks(philo);
		if (found_stop_case(philo))
			break ;
		go_sleep(philo);
		usleep(100);
	}
	return (1);
}

void	go_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->meals_lock);
	philo->meals_eaten += 1;
	philo->last_meal_timestamp = get_timestamp();
	pthread_mutex_unlock(&philo->shared->meals_lock);
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
	pthread_mutex_lock(&philo->shared->write_lock);
	if (!philo->params->all_finished && philo->params->a_philo_died)
	{
		pthread_mutex_unlock(&philo->shared->write_lock);
		log_action("died", philo);
		return ;
	}
	pthread_mutex_unlock(&philo->shared->write_lock);
}
