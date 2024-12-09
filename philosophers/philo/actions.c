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
#include <unistd.h>

void	take_forks(int *left_fork, int *right_fork, t_philo *philo)
{
	int	swap;

	swap = 0;
	*left_fork = philo->id;
	*right_fork = (philo->id + 1) % philo->params->total_philo;
	if (philo->id % 2 != 0)
	{
		usleep(100);
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
	take_forks(&left_fork, &right_fork, philo);
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
	if (found_stop_cases(philo))
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

	ft_usleep(philo, philo->params->time_to_eat);

	pthread_mutex_unlock(&philo->params->fork[left_fork]);
	pthread_mutex_unlock(&philo->params->fork[right_fork]);
	return ;
}

void	ft_usleep(t_philo *philo, long long pause)
{
	long long	start;

	start = get_timestamp();
	while ((get_timestamp() - start) < pause && !found_stop_cases(philo))
		usleep(1000);
}

void	go_sleep_think(t_philo *philo)
{
	if (found_stop_cases(philo))
		return ;
	log_action("is sleeping", philo);
	ft_usleep(philo, philo->params->time_to_sleep);
	log_action("is thinking", philo);
}
