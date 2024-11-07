#include "./philo.h"

long long	ft_atoll(char *num) {
	long long	sum;

	sum = 0;
	while (*num && (*num >= 48 && *num <= 57))
	{
		sum = sum * 10 + (*num - '0');
		num++;
	}
  return (sum);
}

int ft_atoi(char *num) {
  int sum;
  int sign;

  sign = 1;
  sum = 0;
  if (*num == '-' || *num == '+') {
    if (*num == '-')
      sign = -1;
    num++;
  }
  while (*num && (*num >= 48 && *num <= 57)) {
    sum = sum * 10 + (*num - '0');
    num++;
  }
  return (sum * sign);
}

size_t ft_strlen(char *str) {
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int lock_fork(pthread_mutex_t *fork)
{
  // pthread_mutex_lock(fork);
  if(pthread_mutex_lock(fork) == 0)
    return (1);
  return (0);
}

int unlock_fork(pthread_mutex_t *fork)
{
  // pthread_mutex_unlock(fork);
  if (pthread_mutex_unlock(fork) == 0)
    return (1);
  return (0);
}

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












