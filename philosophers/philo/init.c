#include "./philo.h"

t_params *handle_args(int argc, char **argv)
{

	int			    	meals_arg;
  t_params      *params;

	meals_arg = 0;
  if (argc != 5 && argc != 6) {
	    fprintf(stderr, "ERROR ARGUMENTS\n");
		exit (1); }
	if (argc == 6 && argv[5] && is_digits(argv[5]) && ft_atoi(argv[5]) > 0)
		meals_arg = ft_atoi(argv[5]);
	params = malloc(sizeof(t_params));
	if (!params)
  {  
    fprintf(stderr, "ERROR MEMORY ALLOCATION\n");
		exit (1);
  }
  set_params(params, ft_atoi(argv[1]), ft_atoll(argv[2]), ft_atoll(argv[3]),
                ft_atoll(argv[4]), meals_arg);
  if (params->total_philo <= 0 || params->total_philo > 200)
  {
    free(params);
    fprintf(stderr, "PHILOSOPHERS SHOULD BE MORE THAN 1 AND LESS THAN 200\n");
    exit (1);
  }
  return (params);
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
  shared->total_philo_finished_meals = 0;
  return (shared);
}

void  init_forks(t_params *params, t_shared *shared)
{
  int i;

  i = -1;
  while (++i < params->total_philo)
    pthread_mutex_init(&shared->fork[i], NULL);
}

void	set_params(t_params *params, int total_philo, long long time_to_die,
                   long long time_to_eat, long long time_to_sleep, int meals) {
	params->total_philo = total_philo;
	params->time_to_die = time_to_die;
	params->time_to_eat = time_to_eat;
	params->time_to_sleep = time_to_sleep;
	params->max_meals = meals;
  params->limit_meals_reached = false;
  params->timestamp_start = get_timestamp();
}
