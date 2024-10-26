#include "./philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>

t_philo	*create_philo(int id, t_params *params) {
	t_philo   *philo;
  pthread_t *t;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
  philo->thread = t;
  philo->params = params;
	philo->dead = false;
	philo->sleep = false;
	philo->eat = false;
  pthread_mutex_init(&philo->fork, NULL);
	pthread_mutex_init(philo->shared->fork, NULL);
  printf("PHILOSOPHER NUMBER %d CREATED\n", id);
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
		printf("philo: %d\n", list->curr_philo->id);
		pthread_mutex_destroy(&list->curr_philo->fork);
		tmp = list;
		list = list->next;
		free(tmp->curr_philo);
		free(tmp);
	}
}

void  routine(t_philo *philo)
{
  // a cycle of routine is eating then sleeping then thinking 
  // here i will lock shared fork and philo's fork with mutex for eating when shared fork will be avaible
  // then unlock the mutexs when finish eating
  // then destroy the mutexs
  // then enter in sleep state
}

void	start_routines(t_philo_list *list, t_params *params)
{
  t_monitoring  *monitor;
  t_philo_list  *philosophers;
  bool          revolution;

  if (!list)
    return;
  philosophers = list;
  while (!monitor->philo_died)
  {
    while (philosophers)
    {
      pthread_create(philosophers->curr_philo->thread, NULL, &routine, philosophers->curr_philo); 
      philosophers = philosophers->next;
      pthread_join(*philosophers->curr_philo->thread, NULL);
      // maybe i can use the returned value of phtread_join
    }
    if (philosophers -> next == NULL)
    {
      while (while fork shared is not avaible wait then continu)
        philosophers = list;
    }
  }
}

int main(int argc, char **argv) {
	int				meals_arg;
	t_params		*params;
	t_philo_list	*philo_list;
	t_philo			*philo;
	int				i;

	i = 0;
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

	while (++i <= params->total_philo)
	{
		philo = create_philo(i, params);
		push_philo(&philo_list, philo);
	}
	start_routines(philo_list, params);
	free_philo_list(philo_list);
	free(params);
	return (0);
}
