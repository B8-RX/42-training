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

void	take_philo_fork(int *left_fork, int *right_fork, t_philo *philo)
{
	int	swap;

	swap = 0;
	*left_fork = philo->id;
	*right_fork = (philo->id + 1) % philo->params->total_philo;
	if (philo->id % 2 == 0)
	{
		swap = *left_fork;
		*left_fork = *right_fork;
		*right_fork = swap;
	}
}
void	*routine(void *arg)
{
	t_philo		*philo;
	int	left_fork;
	int	right_fork;

	philo = (t_philo *)arg;
	if (philo->params->total_philo == 1)
		return (NULL);
	while (!all_are_ready(philo->params))
		usleep(50);
	take_philo_fork(&left_fork, &right_fork, philo);
	while (1)
	{
		if (found_stop_cases(philo))
			return (NULL);
		go_eat(philo, left_fork, right_fork);
		go_sleep_think(philo);
	}
	return (NULL);
}

void	go_eat(t_philo *philo, int left_fork, int right_fork)
{
	if (found_philo_died(philo))
		return ;
	pthread_mutex_lock(&philo->params->fork[left_fork]);
	log_action("has taken a fork", philo);
	pthread_mutex_lock(&philo->params->fork[right_fork]);
	log_action("has taken a fork", philo);
	log_action("is eating", philo);
	
	pthread_mutex_lock(&philo->params->meals_lock);
	philo->meals_eaten += 1;
	philo->last_meal_timestamp = get_timestamp();
	pthread_mutex_unlock(&philo->params->meals_lock);

	usleep(philo->params->time_to_eat * 1000);

	pthread_mutex_unlock(&philo->params->fork[left_fork]);
	pthread_mutex_unlock(&philo->params->fork[right_fork]);
	return ;
}

void	go_sleep_think(t_philo *philo)
{
	if (found_philo_died(philo))
		return ;
	log_action("is sleeping", philo);
	usleep(philo->params->time_to_sleep * 1000);
}

void	go_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->params->write_lock);
	if (!philo->params->all_finished && philo->params->a_philo_died)
	{
		printf("%lld %d died\n", get_timestamp() - philo->params->timestamp_start,
			philo->id + 1);
		pthread_mutex_unlock(&philo->params->write_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->params->write_lock);
}
