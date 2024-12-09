/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 04:07:05 by ssghioua          #+#    #+#             */
/*   Updated: 2024/12/09 04:07:10 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	init_philo(t_params *params)
{
	int				i;
	t_philo			*philo;
	
	i = -1;
	params->philo_list = NULL;
	while (++i < params->total_philo)
	{
		philo = create_philo(i, params);
		if (!philo)
		{
			clean_mutex(params, params->total_philo);
			clean_data(params);
			printf("Error: philos init\n");
			exit(EXIT_FAILURE);
		}
		add_philo_list(philo, params);
	}
}

t_philo	*create_philo(int id, t_params *params)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->params = params;
	philo->meals_eaten = 0;
	philo->finished_meals = false;
	philo->last_meal_timestamp = get_timestamp();
	return (philo);
}

void	add_philo_list(t_philo *philo, t_params *params)
{
	t_philo_list	*new_node;
	t_philo_list	*current;

	new_node = malloc(sizeof(t_philo_list));
	if (!new_node)
		return ;
	new_node->curr_philo = philo;
	new_node->next = NULL;
	if (!params->philo_list)
		params->philo_list = new_node;
	else
	{
		current = params->philo_list;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

void	handle_single_philo(t_philo_list *list)
{
	log_action("is thinking", list->curr_philo);
	log_action("has taken a fork", list->curr_philo);
	pthread_mutex_lock(&list->curr_philo->params->write_lock);
	list->curr_philo->params->a_philo_died = true;
	pthread_mutex_unlock(&list->curr_philo->params->write_lock);
	usleep(list->curr_philo->params->time_to_die * 1000);
	pthread_mutex_lock(&list->curr_philo->params->display_lock);
	printf("%lld %d died\n", get_timestamp() - list->curr_philo->params->timestamp_start,
		list->curr_philo->id + 1);
	pthread_mutex_unlock(&list->curr_philo->params->display_lock);
}

void	free_philo_list(t_philo_list *list)
{
	t_philo_list	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->curr_philo);
		free(tmp);
	}
}
