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

t_params	*set_params(char **argv, bool meals_arg, int max_meals)
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
	params->meals_arg = meals_arg;
	params->max_meals = max_meals;
	params->all_finished = false;
	params->a_philo_died = false;
	params->timestamp_start = get_timestamp();
	params->philos_ready = false;
	return (params);
}

t_shared	*init_shared(t_params *params)
{
	t_shared	*shared;

	shared = malloc (sizeof(t_shared));
	if (!shared)
	{
		free(params);
		exit (1);
	}
	shared->fork = malloc(sizeof(pthread_mutex_t) * params->total_philo);
	if (!shared->fork)
	{
		free(shared);
		free(params);
		exit (1);
	}
	if (pthread_mutex_init(&shared->rw_lock, NULL) != 0)
	{
		free(shared->fork);
		free(shared);
		free(params);
		exit (1);
	}
	if (pthread_mutex_init(&shared->meals_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&shared->rw_lock);
		free(shared->fork);
		free(shared);
		free(params);
		exit (1);
	}
	if (pthread_mutex_init(&shared->launcher_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&shared->rw_lock);
		pthread_mutex_destroy(&shared->meals_lock);
		free(shared->fork);
		free(shared);
		free(params);
		exit (1);
	}
	if (pthread_mutex_init(&shared->print_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&shared->rw_lock);
		pthread_mutex_destroy(&shared->meals_lock);
		pthread_mutex_destroy(&shared->launcher_lock);
		free(shared->fork);
		free(shared);
		free(params);
		exit (1);
	}
	if (pthread_mutex_init(&shared->satiate_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&shared->rw_lock);
		pthread_mutex_destroy(&shared->meals_lock);
		pthread_mutex_destroy(&shared->launcher_lock);
		pthread_mutex_destroy(&shared->print_lock);
		free(shared->fork);
		free(shared);
		free(params);
		exit (1);
	}
	if (pthread_mutex_init(&shared->end_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&shared->rw_lock);
		pthread_mutex_destroy(&shared->meals_lock);
		pthread_mutex_destroy(&shared->launcher_lock);
		pthread_mutex_destroy(&shared->print_lock);
		pthread_mutex_destroy(&shared->satiate_lock);
		free(shared->fork);
		free(shared);
		free(params);
		exit (1);
	}
	return (shared);
}

void	init_philo_list(t_params *params, t_philo_list **list, t_shared *shared)
{
	int		i;
	t_philo	*philo;

	i = -1;
	*list = NULL;
	while (++i < params->total_philo)
	{
		philo = create_philo(i, params);
		philo->shared = shared;
		push_philo(list, philo);
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
	philo->last_meal_timestamp = 0;
	return (philo);
}

void	push_philo(t_philo_list **list, t_philo *philo)
{
	t_philo_list	*new_node;
	t_philo_list	*current;

	new_node = malloc(sizeof(t_philo_list));
	if (!new_node)
		return ;
	new_node->curr_philo = philo;
	new_node->next = NULL;
	if (!*list)
		*list = new_node;
	else
	{
		current = *list;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}
