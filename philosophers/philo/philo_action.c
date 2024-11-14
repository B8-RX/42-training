#include "./philo.h"

void  go_eat(t_philo *philo)
{
  set_state(philo, EAT);
  log_action("is eating", philo);
  usleep(philo->params->time_to_eat * 1000);
}

void  go_sleep(t_philo *philo)
{
  set_state(philo, SLEEP);
  log_action("is sleeping", philo);
  usleep(philo->params->time_to_sleep * 1000);
}

void  go_die(t_philo *philo)
{
  set_state(philo, DEAD);
  log_action("died", philo);
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
  pthread_mutex_lock(&philo->shared->fork[left_fork]);
  log_action("has taken a fork", philo);
  pthread_mutex_lock(&philo->shared->fork[right_fork]);
  log_action("has taken a fork", philo);
  return (true);    
}

void  release_forks(t_philo *philo)
{
  int left_fork;
  int right_fork;
  int swap;

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
