/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 04:12:35 by ssghioua          #+#    #+#             */
/*   Updated: 2024/11/22 04:12:36 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

t_params	*set_params(char **argv, int max_meals)
{
	t_params	*params;

	params = malloc(sizeof(t_params));
	if (!params)
	{
		fprintf(stderr, "ERROR MEMORY ALLOCATION\n");
		exit (1);
	}
	params->total_philo = ft_atoi(argv[1]);
	params->total_philo_finished_meals = 0;
	params->time_to_die = (long long)ft_atoi(argv[2]);
	params->time_to_eat = (long long)ft_atoi(argv[3]);
	params->time_to_sleep = (long long)ft_atoi(argv[4]);
	params->max_meals = max_meals;
	params->all_finished = false;
	params->a_philo_died = false;
	params->timestamp_start = get_timestamp();
	return (params);
}

void	init_mutex(t_params *params)
{

	params->fork = malloc(sizeof(pthread_mutex_t) * params->total_philo);
	if (!params->fork)
	{
		free(params);
		exit (1);
	}
	if (pthread_mutex_init(&params->write_lock, NULL) != 0)
	{
		free(params->fork);
		free(params);
		exit (1);
	}
	if (pthread_mutex_init(&params->meals_lock, NULL) != 0)
	{
		free(params->fork);
		pthread_mutex_destroy(&params->write_lock);
		pthread_mutex_destroy(&params->meals_lock);
		free(params);
		exit (1);
	}
}

void	init_forks(t_params *params)
{
	int	i;

	i = -1;
	while (++i < params->total_philo)
		pthread_mutex_init(&params->fork[i], NULL);
}

void	init_philo(t_params *params)
{
	int				i;
	t_philo			*philo;
	
	i = -1;
	params->philo_list = NULL;
	while (++i < params->total_philo)
	{
		philo = create_philo(i, params);
		push_philo(philo, params);
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
	philo->is_ready = false;
	return (philo);
}

void	push_philo(t_philo *philo, t_params *params)
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
