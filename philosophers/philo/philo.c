#include "./philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

t_philo	*create_philo(int id, t_params *params) {
	t_philo   *philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
  philo->params = params;
  philo->meals_eaten = 0;
  philo->last_meal_timestamp = 0;
  return (philo);
}

bool is_digits(char *arg) {
  while (arg && *arg) {
    if (*arg < 48 || *arg > 57)
      return (false);
    arg++;
  }
  return (true);
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

long long get_timestamp()
{
  struct timeval  tv; 

  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	set_params(t_params *params, int total_philo, long long time_to_die,
                   long long time_to_eat, long long time_to_sleep, int meals) {
	params->total_philo = total_philo;
	params->total_philo_finished_meals = 0;
	params->time_to_die = time_to_die;
	params->time_to_eat = time_to_eat;
	params->time_to_sleep = time_to_sleep;
	params->max_meals = meals;
  params->is_game_over = false;
  params->timestamp_start = get_timestamp();
}

void	free_philo_list(t_philo_list *list)
{
	t_philo_list *tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->curr_philo);
		free(tmp);
	}
}

void  log_action(const char *action, t_philo *philo)
{
    printf("%lld %d %s\n", get_timestamp() - philo->params->timestamp_start, philo->id + 1, action);
}

void  go_eat(t_philo *philo)
{
  log_action("is eating", philo);
  usleep(philo->params->time_to_eat * 1000);
  pthread_mutex_lock(&philo->shared->write_lock);
  philo->meals_eaten += 1;
  // printf("PHILO %d MEALS %d\n", philo->id + 1, philo->meals_eaten);
  // printf("TOTAL FINISHED %d\n", philo->params->total_philo_finished_meals);
  philo->last_meal_timestamp = get_timestamp();
  pthread_mutex_unlock(&philo->shared->write_lock);

}

void  go_sleep(t_philo *philo)
{
  log_action("is sleeping", philo);
  usleep(philo->params->time_to_sleep * 1000);
}

void  go_die(t_philo *philo)
{
  log_action("died", philo);
  usleep(philo->params->time_to_die * 1000);
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
      pthread_mutex_lock(&philo->shared->write_lock);
      if (philo->params->is_game_over)
      {
        pthread_mutex_unlock(&philo->shared->write_lock);
        return (NULL);
      }
      if (philo->last_meal_timestamp > 0 && (get_timestamp() - philo->last_meal_timestamp) >= philo->params->time_to_die)
      {
        go_die(philo);
        philo->params->is_game_over = true;
        pthread_mutex_unlock(&philo->shared->write_lock);
        return (NULL);
      }
      if (philo->params->max_meals != -1 && philo->meals_eaten == philo->params->max_meals)
        philo->params->total_philo_finished_meals += 1;
      if (philo->params->total_philo_finished_meals == philo->params->total_philo)
      {
        philo->params->is_game_over = true;
        pthread_mutex_unlock(&philo->shared->write_lock);
        return (NULL);  
      }
      pthread_mutex_unlock(&philo->shared->write_lock);
      current = current->next;
    }
    usleep(500);
  }
 return (NULL); 
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

void  *routine(void *arg)
{
  t_philo *philo;
   
  philo = (t_philo*)arg;
  if (philo->params->total_philo == 1)
    return (NULL);
  while (1)
  {
    pthread_mutex_lock(&philo->shared->write_lock);
    if (philo->params->is_game_over)
    {
      pthread_mutex_unlock(&philo->shared->write_lock);
      break;
    }
    pthread_mutex_unlock(&philo->shared->write_lock);
    log_action("is thinking", philo);
    if (handle_forks(philo))
    {
      go_eat(philo);
      release_forks(philo);
      go_sleep(philo);
      usleep(100);
    }
  }
  return (NULL);
}

void	create_threads(t_philo_list *list)
{
  t_philo_list  *philosophers;
  pthread_t       monitor_thread;
  size_t        list_length;

  list_length = 0;
  philosophers = list;
  if (pthread_create(&monitor_thread, NULL, &monitor, list) != 0)
  {
    fprintf(stderr, "Error on thread creation for monitor\n");
    exit(EXIT_FAILURE);
  }
  while (philosophers)
  {
    list_length++;
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
  if (list_length == 1)
  {
    log_action("is thinking", list->curr_philo);
    log_action("has taken a fork", list->curr_philo);
    pthread_mutex_lock(&list->curr_philo->shared->write_lock);
    list->curr_philo->params->is_game_over = true;
    pthread_mutex_unlock(&list->curr_philo->shared->write_lock);
    go_die(list->curr_philo);
  }
  pthread_join(monitor_thread, NULL);
}

int main(int argc, char **argv) {
	t_params		  *params;
	t_philo_list	*philo_list;
	int				    i;
  t_shared      *shared;

  params = handle_args(argc, argv);
  shared = init_shared(params);
  init_forks(params, shared);
  init_philo(params, &philo_list, shared);
	create_threads(philo_list);
  i = -1;
  while (++i < params->total_philo)
    pthread_mutex_destroy(&shared->fork[i]);  
  pthread_mutex_destroy(&shared->write_lock);
  pthread_mutex_destroy(&shared->meals_mutex);
  free(shared->fork);
  free(shared);
  free_philo_list(philo_list);
	free(params);
	return (0);
}
