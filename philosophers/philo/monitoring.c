/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 04:03:57 by ssghioua          #+#    #+#             */
/*   Updated: 2024/11/22 04:03:58 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"
#include <unistd.h>

void	log_action(const char *action, t_philo *philo)
{
	if (found_stop_cases(philo))
		return ;
	pthread_mutex_lock(&philo->params->write_lock);
	printf("%lld %d %s\n", get_timestamp() - philo->params->timestamp_start,
		philo->id + 1, action);
	pthread_mutex_unlock(&philo->params->write_lock);
}

void	*monitor(void *arg)
{
	t_philo_list	*philo_list;
	int				pause;

	philo_list = (t_philo_list *)arg;
	if (philo_list->curr_philo->params->total_philo == 1)
		return (NULL);
	if (philo_list->curr_philo->params->total_philo > 100)
		pause = 10;
	else
		pause = 100;
	pthread_mutex_lock(&philo_list->curr_philo->params->ready_lock);
	while (!philo_list->curr_philo->params->ready)
	{
		pthread_mutex_unlock(&philo_list->curr_philo->params->ready_lock);
		usleep(200);
		pthread_mutex_lock(&philo_list->curr_philo->params->ready_lock);
	}
	pthread_mutex_unlock(&philo_list->curr_philo->params->ready_lock);
	while (1)
	{
		if (found_stop_cases(philo_list->curr_philo))
			return (NULL);
		if (is_philo_starve(philo_list->curr_philo->params))
			return (NULL);
		if (all_philo_satiate(philo_list->curr_philo->params))
			return (NULL);
		usleep(pause);
	}
	return (NULL);
}
