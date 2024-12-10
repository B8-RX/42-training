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

void	log_action(const char *action, t_philo *philo)
{
	if (found_stop_cases(philo))
		return ;
	pthread_mutex_lock(&philo->params->display_lock);
	printf("%lld %d %s\n", get_timestamp() - philo->params->timestamp_start,
		philo->id + 1, action);
	pthread_mutex_unlock(&philo->params->display_lock);
}

bool	monitor_check_stop_cases(t_philo *philo)
{	
	if (is_philo_starve(philo))
		return (true);
	if (philo->params->max_meals != -1)
	{
		if (all_philo_satiate(philo))
			return (true);
	}	
	return (false);
}

void	*monitor(void *arg)
{
	t_philo_list	*philo_list;
	t_philo_list	*current;

	philo_list = (t_philo_list *)arg;
	if (philo_list->curr_philo->params->total_philo == 1)
		return (handle_single_philo(philo_list), NULL);
	while (!all_are_ready(philo_list->curr_philo->params))
		usleep(5);
	while (1)
	{
		current = philo_list;
		while (current)
		{
			if (monitor_check_stop_cases(current->curr_philo))
				return (NULL);
			current = current->next;
			usleep(1);
		}
	}
	return (NULL);
}
