#include "./philo.h"

void  *routine(void *arg)
{
  t_philo *philo;

  philo = (t_philo*)arg;
   if (philo->params->total_philo == 1)
  {
    log_action("has taken a fork", philo);
    go_die(philo);
    return (NULL);
  }
  while (1)
  {
    log_action("is thinking", philo);
    pthread_mutex_lock(&philo->shared->write_lock); 
    if (philo->shared->total_philo_finished_meals == philo->params->total_philo)
    {
      pthread_mutex_unlock(&philo->shared->write_lock); 
      break;
    }
    pthread_mutex_unlock(&philo->shared->write_lock); 
    handle_forks(philo);
    go_eat(philo);
    release_forks(philo);
    go_sleep(philo);
  }
  return (NULL);
}

void	start_routines(t_philo_list *list)
{
  t_philo_list  *philosophers;

  philosophers = list;
  while (philosophers)
  {
    if (pthread_create(&philosophers->curr_philo->thread, NULL, &routine, philosophers->curr_philo) != 0)
    {
      fprintf(stderr, "Error on thread creation for philosopher %d\n", philosophers->curr_philo->id);
      exit(EXIT_FAILURE);
    }
    philosophers = philosophers->next;
  }
  philosophers = list;
  while (philosophers)
  {
    pthread_join(philosophers->curr_philo->thread, NULL);
    philosophers = philosophers->next;
  }
}
