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

void	release_forks(t_philo *philo)
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
	pthread_mutex_unlock(&philo->params->fork[left_fork]);
	pthread_mutex_unlock(&philo->params->fork[right_fork]);
}

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
	if (found_stop_cases(philo))
		return (false);
	pthread_mutex_lock(&philo->params->fork[left_fork]);
	pthread_mutex_lock(&philo->params->fork[right_fork]);
	if (found_stop_cases(philo))
	{
		pthread_mutex_unlock(&philo->params->fork[right_fork]);
		pthread_mutex_unlock(&philo->params->fork[left_fork]);
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
		return (0);
	while (!all_are_ready(philo->params))
		usleep(50);
	while (1)
	{
		if (found_stop_cases(philo))
			break ;
		log_action("is thinking", philo);
		if (!handle_forks(philo))
			break ;
		go_eat(philo);
		release_forks(philo);
		usleep(100);
		if (found_stop_cases(philo))
			break ;
		go_sleep(philo);
	}
	return (0);
}

void	go_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->params->write_lock);
	philo->meals_eaten += 1;
	philo->last_meal_timestamp = get_timestamp();
	pthread_mutex_unlock(&philo->params->write_lock);
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
	pthread_mutex_lock(&philo->params->write_lock);
	if (!philo->params->all_finished && philo->params->a_philo_died)
	{
		pthread_mutex_unlock(&philo->params->write_lock);
		log_action("died", philo);
		return ;
	}
	pthread_mutex_unlock(&philo->params->write_lock);
}
