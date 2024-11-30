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
	pthread_mutex_lock(&philo->shared->fork[left_fork]);
	pthread_mutex_lock(&philo->shared->fork[right_fork]);
	log_action("has taken a fork", philo);
	log_action("has taken a fork", philo);
	return (true);
}

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
	pthread_mutex_unlock(&philo->shared->fork[left_fork]);
	pthread_mutex_unlock(&philo->shared->fork[right_fork]);
}

bool	check_philos_ready(t_philo *philo)
{
	bool	philos_ready;

	pthread_mutex_lock(&philo->shared->launcher_lock);
	philos_ready = philo->params->philos_ready;
	pthread_mutex_unlock(&philo->shared->launcher_lock);
	return (philos_ready);
}

int	routine(void *arg)
{
	t_philo		*philo;
	int			nb_philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->shared->rw_lock);
	nb_philo = philo->params->total_philo;	
	pthread_mutex_unlock(&philo->shared->rw_lock);
	while (check_philos_ready(philo) == false)
		usleep(5);
	if (nb_philo == 1)
		return (1);
	while (1)
	{
		if (found_stop_case(philo))
			break ;
		handle_forks(philo);
		go_eat(philo);
		release_forks(philo);
		if (found_stop_case(philo))
			break ;
		go_sleep(philo);
		if (found_stop_case(philo))
			break ;
		log_action("is thinking", philo);
	}
	return (1);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_timestamp();
	while ((get_timestamp() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	go_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->meals_lock);
	philo->meals_eaten += 1;
	philo->last_meal_timestamp = get_timestamp();
	pthread_mutex_unlock(&philo->shared->meals_lock);
	log_action("is eating", philo);
	ft_usleep(philo->params->time_to_eat);
}

void	go_sleep(t_philo *philo)
{
	log_action("is sleeping", philo);
	ft_usleep(philo->params->time_to_sleep);
}

void	go_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->rw_lock);
	if (!philo->params->all_finished)
	{
		pthread_mutex_unlock(&philo->shared->rw_lock);
		log_action("died", philo);
		return ;
	}
	pthread_mutex_unlock(&philo->shared->rw_lock);
}
