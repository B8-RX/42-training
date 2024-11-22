/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 03:53:27 by ssghioua          #+#    #+#             */
/*   Updated: 2024/11/22 03:53:29 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void  init_philo_thr(t_philo_list *list, int *list_length)
{
  t_philo_list  *philosophers;
  int           len;

  philosophers = list;
  len = 0;
  while (philosophers)
  {
    len++;
    if (pthread_create(&philosophers->curr_philo->thread, NULL, (void *)&routine, philosophers->curr_philo) != 0)
    {
      fprintf(stderr, "Error on thread creation for philosopher %d\n", philosophers->curr_philo->id);
      exit(EXIT_FAILURE);
    }
    philosophers = philosophers->next;
  }
  *list_length = len;
}

void	create_threads(t_philo_list *list)
{
  t_philo_list  *philosophers;
  pthread_t       monitor_thread;
  int        list_length = 0;

  philosophers = list;
  if (pthread_create(&monitor_thread, NULL, &monitor, list) != 0)
  {
    fprintf(stderr, "Error on thread creation for monitor\n");
    exit(EXIT_FAILURE);
  }
  init_philo_thr(list, &list_length);
  if (list_length == 1)
    handle_single_philo(list);
  philosophers = list;
  while (philosophers)
  {
    pthread_join(philosophers->curr_philo->thread, NULL);
    philosophers = philosophers->next;
  }
  pthread_join(monitor_thread, NULL);
}

void  init_forks(t_params *params, t_shared *shared)
{
  int i;

  i = -1;
  while (++i < params->total_philo)
    pthread_mutex_init(&shared->fork[i], NULL);
}

bool  handle_forks(t_philo  *philo)
{
  int             left_fork;
  int             right_fork;
  int             swap;
  
  left_fork = philo->id;
  right_fork = (philo->id + 1) % philo->params->total_philo;
  if (philo->id % 2 == 0)
  {
    swap = left_fork;
    left_fork = right_fork;
    right_fork = swap;
  }
  if (found_stop_cases(philo))
    return (false);
  pthread_mutex_lock(&philo->shared->fork[left_fork]);
  if (found_stop_cases(philo))
  {
    pthread_mutex_unlock(&philo->shared->fork[left_fork]);
    return (false);
  }
  log_action("has taken a fork", philo);
  pthread_mutex_lock(&philo->shared->fork[right_fork]);
  log_action("has taken a fork", philo);
  return (true);    
}

void  release_forks(t_philo *philo)
{
  int left_fork;
  int right_fork;
  int             swap;

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
