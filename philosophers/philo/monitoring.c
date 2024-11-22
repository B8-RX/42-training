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

bool  monitor_check_stop_cases(t_philo *philo)
{
  if (found_philo_died(philo) || is_philo_starve(philo) || all_philo_satiate(philo))
    return (true);
  return (false);
}

void  *monitor(void *arg)
{
  t_philo_list  *philo_list;
  t_philo_list  *current;
  t_philo       *philo;

  philo_list = (t_philo_list *)arg;
  while (1)
  {
    current = philo_list;
    while (current)
    {
      philo = current->curr_philo;
      if (monitor_check_stop_cases(philo))
        return (NULL);
      current = current->next;
      usleep(100);
    }
  }
 return (NULL); 
}
