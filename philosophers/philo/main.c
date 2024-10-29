#include "./philo.h"
#include <cstring>
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
	philo->dead = false;
	philo->eat = false;
	philo->sleep = false;
  printf("PHILOSOPHER NUMBER %d CREATED\n", id + 1);
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

void	handle_params(t_params **params, int total_philo, long long time_to_die,
                   long long time_to_eat, long long time_to_sleep, int meals) {
	(*params)->total_philo = total_philo;
	(*params)->time_to_die = time_to_die;
	(*params)->time_to_eat = time_to_eat;
	(*params)->time_to_sleep = time_to_sleep;
	(*params)->total_meals = meals;
	printf("HANDLE PARAMS FINISH\n");
}

void	free_philo_list(t_philo_list *list)
{
	t_philo_list *tmp;

	while (list)
	{
		printf("freeing philo: %d\n", list->curr_philo->id + 1);
		tmp = list;
		list = list->next;
		free(tmp->curr_philo);
		free(tmp);
	}
}

unsigned long get_timestamp(void)
{
  struct timeval  tv; 

  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

bool  is_time_over(unsigned long waiting_time, int time_to_die)
{
  return ((get_timestamp() - waiting_time) >= time_to_die);
}

bool  handle_forks(t_philo  *philo)
{
  int             philo_fork_index;
  int             shared_fork_index;
  unsigned long   waiting_time;

  philo_fork_index = philo->id;
  shared_fork_index = (philo->id + 1) % philo->params->total_philo;
  if (pthread_mutex_lock(&philo->shared->fork[philo_fork_index]) == 0)
  {
    printf("%lu %d has taken a fork\n", get_timestamp(), philo->id + 1);
    waiting_time = get_timestamp();

    while (pthread_mutex_lock(&philo->shared->fork[shared_fork_index]) != 0)
    {
      if (is_time_over(waiting_time, philo->params->time_to_die))
      {
        printf("%lu %d died\n", get_timestamp(), philo->id + 1);
        philo->eat = false;
        philo->dead = true;
        pthread_mutex_unlock(&philo->shared->fork[philo_fork_index]);
        return (false);
      }
      usleep(100);
    }
    printf("%lu %d has taken a fork\n", get_timestamp(), philo->id + 1);
    return (true);
  }
  return (false);
}

void  release_forks(t_philo *philo)
{
  int philo_fork_index;
  int shared_fork_index;

  philo_fork_index = philo->id;
  shared_fork_index = (philo->id + 1) % philo->params->total_philo;
  pthread_mutex_unlock(&philo->shared->fork[philo_fork_index]);
  pthread_mutex_unlock(&philo->shared->fork[shared_fork_index]);
  philo->eat = false;
}

void  reset_states(t_philo *philo)
{
  philo->dead = false;
  philo->eat = false;
  philo->sleep = false;
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
  if (n == 0)
    return (0);
  while (*s1 && *s1 == *s2 && --n)
  {
    s1++;
    s2++;
  }
  return ((unsigned char)*s1 - (unsigned char)*s2);
}

void  set_state(t_philo *philo, char *state)
{
  reset_states(philo);
  if (ft_strncmp(state, "dead", 4) == 0)
    philo->dead = true;
  else if (ft_strncmp(state, "eat", 3) == 0)
    philo->eat = true;
  else if (ft_strncmp(state, "sleep", 5) == 0)
      philo->sleep = true;
}

void  go_eat(t_philo *philo)
{
    set_state(philo, "eat");
    printf("%lu %d is eating\n", get_timestamp(), philo->id + 1);
    usleep(philo->params->time_to_eat * 1000);
}

void  go_sleep(t_philo *philo)
{
    set_state(philo, "sleep");
    printf("%lu %d is sleeping\n", get_timestamp(), philo->id + 1);
    usleep(philo->params->time_to_sleep * 1000);
}

void  go_die(t_philo *philo)
{
  reset_states(philo);
  set_state(philo, "dead");
  usleep(philo->params->time_to_die * 1000);
  printf("%lu %d died\n", get_timestamp(), philo->id + 1);
}

void  *routine(void *arg)
{
  t_philo         *philo;

  philo = (t_philo*)arg;
  if (philo->params->total_philo == 1)
  {
    printf("%lu %d has taken a fork\n", get_timestamp(), philo->id + 1);
    go_die(philo);
    return (NULL);
  }
  while (!philo->dead)
  {
    if (!handle_forks(philo))
      continue;
    go_eat(philo);
    release_forks(philo);
    go_sleep(philo);
    reset_states(philo);
    printf("%lu %d is thinking\n", get_timestamp(), philo->id + 1);
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

int main(int argc, char **argv) {
	int			    	meals_arg;
	t_params		  *params;
	t_philo_list	*philo_list;
	t_philo			  *philo;
	int				    i;
  t_shared      *shared;

	meals_arg = -1;
	philo_list = NULL;
	if (argc != 5 && argc != 6) {
	    printf("ERROR ARGUMENTS\n");
		exit(1);
	}
	if (argc == 6 && argv[5] && is_digits(argv[5]) && ft_atoi(argv[5]) > 0)
		meals_arg = ft_atoi(argv[5]);
	params = malloc(sizeof(t_params));
	if (!params)
		return (1);
	handle_params(&params, ft_atoi(argv[1]), ft_atoll(argv[2]), ft_atoll(argv[3]),
                ft_atoll(argv[4]), meals_arg);
	printf("total philo= %d\nto die= %lld\nto eat = %lld\nto sleep = %lld\ntotal "
         "meals = %d\n",
    params->total_philo, params->time_to_die, params->time_to_eat,
    params->time_to_sleep, params->total_meals);
  if (params->total_philo <= 0 || params->total_philo > 200)
  {
    free(params);
    fprintf(stderr, "PHILOSOPHERS SHOULD BE MORE THAN 1 AND LESS THAN 200\n");
    exit(1);
  }
  shared = malloc (sizeof(t_shared));
  if (!shared)
  {
    free(params);
    exit(1);
  }
  shared->fork = malloc(sizeof(pthread_mutex_t) * params->total_philo);
  if (!shared->fork)
  {
    free(shared);
    free(params);
    exit(1);
  }
	i = -1;
  while (++i < params->total_philo)
    pthread_mutex_init(&shared->fork[i], NULL);
  i = -1;
	while (++i < params->total_philo)
	{
		philo = create_philo(i, params);
    philo->shared = shared;
		push_philo(&philo_list, philo);
	}
	start_routines(philo_list);
  i = -1;
  while (++i < params->total_philo)
    pthread_mutex_destroy(&shared->fork[i]);
  free(shared->fork);
  free(shared);
  free_philo_list(philo_list);
	free(params);
	return (0);
}
