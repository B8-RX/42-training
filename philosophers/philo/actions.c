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
	t_philo	*philo;
	int		left_fork;
	int		right_fork;

	philo = (t_philo *)arg;
	if (philo->params->total_philo == 1)
		return (NULL);
	while (!all_are_ready(philo->params))
		usleep(50);
	take_forks(&left_fork, &right_fork, philo);
	while (1 && !found_stop_cases(philo))
	{
		go_eat(philo, left_fork, right_fork);
		go_sleep(philo);
		go_think(philo);
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

void	go_sleep(t_philo *philo)
{
	if (found_stop_cases(philo))
		return ;
	log_action("is sleeping", philo);
	ft_usleep(philo, philo->params->time_to_sleep);
}

void	go_think(t_philo *philo)
{
	log_action("is thinking", philo);
	pthread_mutex_lock(&philo->params->meals_lock);
	pthread_mutex_lock(&philo->params->global_lock);
	while ((philo->params->time_to_die - (get_timestamp()
				- philo->last_meal_timestamp) > philo->params->time_to_eat)
		&& philo->params->a_philo_died == 0)
	{
		pthread_mutex_unlock(&philo->params->global_lock);
		pthread_mutex_unlock(&philo->params->meals_lock);
		ft_usleep(philo, 1);
		pthread_mutex_lock(&philo->params->meals_lock);
		pthread_mutex_lock(&philo->params->global_lock);
	}
	pthread_mutex_unlock(&philo->params->global_lock);
	pthread_mutex_unlock(&philo->params->meals_lock);
}
