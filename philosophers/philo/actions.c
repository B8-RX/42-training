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

int	eat(t_philo *philo, size_t left_fork, size_t right_fork)
{

	pthread_mutex_lock(&philo->params->fork[left_fork]);
	log_action("has taken a fork", philo);
	pthread_mutex_lock(&philo->params->fork[right_fork]);
	log_action("has taken a fork", philo);
	log_action("is eating", philo);

	pthread_mutex_lock(&philo->params->meals_lock);
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->params->meals_lock);

	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal_timestamp = get_timestamp();
	pthread_mutex_unlock(&philo->last_meal_lock);

	ft_usleep(philo, philo->params->time_to_eat);

	pthread_mutex_unlock(&philo->params->fork[left_fork]);
	pthread_mutex_unlock(&philo->params->fork[right_fork]);
	return (1);
}

int	routine(void *arg)
{
	t_philo		*philo;
	int	left_fork;
	int	right_fork;
	int	swap;


	philo = (t_philo *)arg;
	if (philo->params->total_philo == 1)
		return (0);
	pthread_mutex_lock(&philo->params->ready_lock);
	while (!philo->params->ready)
	{
		pthread_mutex_unlock(&philo->params->ready_lock);
		usleep(200);
		pthread_mutex_lock(&philo->params->ready_lock);
	}
	left_fork = philo->id;
	right_fork = (philo->id + 1) % philo->params->total_philo;
	if (philo->id % 2 != 0)
	{
		usleep(100);
		swap = left_fork;
		left_fork = right_fork;
		right_fork = swap;
	}
	pthread_mutex_unlock(&philo->params->ready_lock);

	while (1)
	{
		if (found_stop_cases(philo))
			break ;
		if (!eat(philo, left_fork, right_fork))
			break ;
		go_sleep(philo);
		usleep(10);
	}
	return (0);
}

void	ft_usleep(t_philo *philo, long long pause)
{
	long long	start;

	start = get_timestamp();
	while ((get_timestamp() - start) < pause && !found_stop_cases(philo))
		usleep(1000);
}

void	go_sleep(t_philo *philo)
{
	if (found_stop_cases(philo))
		return ;
	log_action("is sleeping", philo);
	ft_usleep(philo, philo->params->time_to_sleep);
	log_action("is thinking", philo);

	pthread_mutex_lock(&philo->params->dead_lock);
	pthread_mutex_lock(&philo->last_meal_lock);
	while ((philo->params->time_to_die - (get_timestamp()
				- philo->last_meal_timestamp)) > (philo->params->time_to_eat * 2 - philo->params->time_to_sleep))
	{
		pthread_mutex_unlock(&philo->params->dead_lock);
		pthread_mutex_unlock(&philo->last_meal_lock);
		ft_usleep(philo, 1);
		pthread_mutex_lock(&philo->params->dead_lock);
		pthread_mutex_lock(&philo->last_meal_lock);
	}
	pthread_mutex_unlock(&philo->params->dead_lock);
	pthread_mutex_unlock(&philo->last_meal_lock);
}
