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
		usleep(100);
		swap = left_fork;
		left_fork = right_fork;
		right_fork = swap;
	}
	// if (found_stop_cases(philo))
	// 	return (false);
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

bool	get_ready(t_params *params)
{
	bool	ready;

	pthread_mutex_lock(&params->ready_lock);
	ready = params->ready;
	pthread_mutex_unlock(&params->ready_lock);
	return (ready);
}

int	routine(void *arg)
{
	t_philo		*philo;
	// int			total_philo;

	philo = (t_philo *)arg;
	// total_philo = philo->params->total_philo;
	if (philo->params->total_philo == 1)
		return (0);
	while (!get_ready(philo->params))
		usleep(100);
	while (1)
	{
		if (found_stop_cases(philo))
			break ;
		if (!handle_forks(philo))
			break ;
		go_eat(philo);
		release_forks(philo);
		if (found_stop_cases(philo))
			break ;
		go_sleep(philo);
	}
	return (0);
}

void	go_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->params->meals_lock);
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->params->meals_lock);
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal_timestamp = get_timestamp();
	pthread_mutex_unlock(&philo->last_meal_lock);
	log_action("is eating", philo);
	ft_usleep(philo, philo->params->time_to_eat);
}

void	ft_usleep(t_philo *philo, long long sleep_time)
{
	long long	start;

	start = get_timestamp();
	while ((get_timestamp() - start) < sleep_time && !found_stop_cases(philo))
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
				- philo->last_meal_timestamp) > philo->params->time_to_eat)
		&& philo->params->a_philo_died == 0)
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

void	go_die(t_philo *philo)
{
		pthread_mutex_lock(&philo->params->dead_lock);
		philo->params->a_philo_died = true;
		pthread_mutex_unlock(&philo->params->dead_lock);
		log_action("died", philo);
		return ;
}
