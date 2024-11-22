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

void	set_params(t_params *params, int total_philo, long long time_to_die,
                   long long time_to_eat, long long time_to_sleep, int meals) {
	params->total_philo = total_philo;
	params->total_philo_finished_meals = 0;
	params->time_to_die = time_to_die;
	params->time_to_eat = time_to_eat;
	params->time_to_sleep = time_to_sleep;
	params->max_meals = meals;
  params->all_finished = false;
  params->a_philo_died = false;
  params->timestamp_start = get_timestamp();
}

t_shared  *init_shared(t_params *params)
{
  t_shared  *shared;

  shared = malloc (sizeof(t_shared));
  if (!shared)
  {
    free(params);
    fprintf(stderr, "ERROR MEMORY ALLOCATION\n");
		exit (1);
  }
  shared->fork = malloc(sizeof(pthread_mutex_t) * params->total_philo);
  if (!shared->fork)
  {
    free(shared);
    free(params);
    fprintf(stderr, "ERROR MEMORY ALLOCATION\n");
		exit (1);
  }
  if (pthread_mutex_init(&shared->write_lock, NULL) != 0)
  {
    free(shared->fork);
    free(shared);
    free(params);
    fprintf(stderr, "ERROR MUTEX INIT\n");
		exit (1);
  }
  return (shared);
}

void  init_philo(t_params *params, t_philo_list **philo_list, t_shared *shared)
{
	int				    i;
	t_philo			  *philo;
	
  i = -1;
  *philo_list = NULL;
  while (++i < params->total_philo)
	{
		philo = create_philo(i, params);
    philo->shared = shared;
		push_philo(philo_list, philo);
	}
}

t_philo	*create_philo(int id, t_params *params) {
	t_philo   *philo;

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

void push_philo(t_philo_list **list, t_philo *philo) {
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
