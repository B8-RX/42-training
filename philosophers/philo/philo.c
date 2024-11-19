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
  philo->finished_meals = false;
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
  params->all_finished = false;
  params->a_philo_died = false;
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
  pthread_mutex_lock(&philo->shared->write_lock);
  philo->meals_eaten += 1;
  philo->last_meal_timestamp = get_timestamp();
  pthread_mutex_unlock(&philo->shared->write_lock);
  log_action("is eating", philo);
  usleep(philo->params->time_to_eat * 1000);
}

void  go_sleep(t_philo *philo)
{
  log_action("is sleeping", philo);
  usleep(philo->params->time_to_sleep * 1000);
}

void  go_die(t_philo *philo)
{
  log_action("died", philo);
}

void  *monitor(void *arg)
{
  t_philo_list  *philo_list;
  t_philo_list  *current;
  t_philo       *philo;
  bool          a_philo_died;
  bool          all_finished;
  long long     time_to_die;
  long long     last_meal_timestamp;
  int           max_meals;
  int           total_philo_finished_meals;
  int           total_philo;


  philo_list = (t_philo_list *)arg;
  while (1)
  {
    current = philo_list;
    while (current)
    {
      philo = current->curr_philo;
      pthread_mutex_lock(&philo->shared->write_lock);
      a_philo_died = philo->params->a_philo_died;
      all_finished = philo->params->all_finished;
      time_to_die = philo->params->time_to_die;
      last_meal_timestamp = philo->last_meal_timestamp;
      max_meals = philo->params->max_meals;
      total_philo_finished_meals = philo->params->total_philo_finished_meals;
      total_philo = philo->params->total_philo;
      pthread_mutex_unlock(&philo->shared->write_lock);
      if (a_philo_died || all_finished)
        return (NULL);
      if (last_meal_timestamp > 0 && (get_timestamp() - last_meal_timestamp) >= time_to_die)
      {
        pthread_mutex_lock(&philo->shared->write_lock);
        philo->params->a_philo_died = true;
        pthread_mutex_unlock(&philo->shared->write_lock);
        go_die(philo);
        return (NULL);
      }
      if (max_meals != -1 && philo->meals_eaten == max_meals && !philo->finished_meals)
      {
        pthread_mutex_lock(&philo->shared->write_lock);
        philo->params->total_philo_finished_meals += 1;
        philo->finished_meals = true;
        if (total_philo_finished_meals == total_philo)
        {
          philo->params->all_finished = true;
          pthread_mutex_unlock(&philo->shared->write_lock);
          return (NULL);  
        }
        pthread_mutex_unlock(&philo->shared->write_lock);
      }
      current = current->next;
    }
    // usleep(10);
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
  pthread_mutex_lock(&philo->shared->write_lock);
  if (philo->params->a_philo_died || philo->params->all_finished)
  {
    pthread_mutex_unlock(&philo->shared->write_lock);
    return (false);
  }
  pthread_mutex_unlock(&philo->shared->write_lock);
  pthread_mutex_lock(&philo->shared->fork[left_fork]);
  pthread_mutex_lock(&philo->shared->write_lock);
  if (philo->params->a_philo_died || philo->params->all_finished)
  {
    pthread_mutex_unlock(&philo->shared->write_lock);
    pthread_mutex_unlock(&philo->shared->fork[left_fork]);
    return (false);
  }
  log_action("has taken a fork", philo);
  pthread_mutex_unlock(&philo->shared->write_lock);
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
    if (philo->params->a_philo_died || philo->params->all_finished)
    {
      pthread_mutex_unlock(&philo->shared->write_lock);
      break;
    }
    pthread_mutex_unlock(&philo->shared->write_lock);

    log_action("is thinking", philo);
    if (!handle_forks(philo))
      break;
    
    pthread_mutex_lock(&philo->shared->write_lock);
    if (philo->params->a_philo_died || philo->params->all_finished)
    {
      pthread_mutex_unlock(&philo->shared->write_lock);
      release_forks(philo);
      break;
    }
    pthread_mutex_unlock(&philo->shared->write_lock);
    
    go_eat(philo);
    release_forks(philo);
    
    pthread_mutex_lock(&philo->shared->write_lock);
    if (philo->params->a_philo_died || philo->params->all_finished)
    {
      pthread_mutex_unlock(&philo->shared->write_lock);
      break;
    }
    pthread_mutex_unlock(&philo->shared->write_lock);
    go_sleep(philo);
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
    go_die(list->curr_philo);
    list->curr_philo->params->a_philo_died = true;
    pthread_mutex_unlock(&list->curr_philo->shared->write_lock);
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
