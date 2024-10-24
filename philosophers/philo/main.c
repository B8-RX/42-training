#include "./philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>

t_philo	*create_philo(int id, long long time_to_die, long long time_to_eat, long long time_to_sleep)
{
	t_philo	*philo;
	

	pthread_mutex_init(&philo->mutex, NULL);
	philo->id = id;
	philo->time_to_die = time_to_die;
	philo->time_to_eat = time_to_eat;
	philo->time_to_sleep = time_to_sleep;
	philo->sleep = false;
	philo->eat = false;
	philo->dead = false;
	printf("PHILOSOPHER NUMBER %d CREATED\n", id);
	return (philo);
}

bool	is_digits(char *arg)
{
	while (arg && *arg)
	{
		if (*arg < 48 || *arg > 57)
			return (false);
		arg++;
	}
	return (true);
}

void	init_list(t_philo_list **philo_list)
{
	*philo_list = malloc(sizeof(t_philo_list));
	(*philo_list)->curr_philo = NULL;
	(*philo_list)->next = NULL;
}

void	push_philo(t_philo_list *list, t_philo *philo)
{
	t_philo	*tmp;

	tmp = philo;
	if (list && list->curr_philo == NULL)
		list->curr_philo = tmp;
	else
	{
		while (list && list->next != NULL)
			list = list->next;
		list->curr_philo = tmp;
		list->next = NULL;
	}
}

void	handle_params(t_params **params, int total_philo, long long time_to_die, long long time_to_eat, long long time_to_sleep, int meals)
{
	(*params)->total_philo = total_philo;
	(*params)->time_to_die = time_to_die;
	(*params)->time_to_eat = time_to_eat;
	(*params)->time_to_sleep = time_to_sleep;
	(*params)->total_meals = meals;
	printf("HANDLE PARAMS FINISH\n");
}

int main(int argc, char **argv)
{
	int				i;
	int				meals_arg;
	t_params		*params;
	t_philo_list	*philo_list;

	i = 0;
	meals_arg = -1;
	if (argc != 5 && argc != 6)
	{
		printf("ERROR ARGUMENTS\n");
		exit(1);
	}
	if (argc == 6 && argv[5] && is_digits(argv[5]) && ft_atoi(argv[5]) > 0)
		meals_arg = ft_atoi(argv[5]);
	params = malloc(sizeof(t_params));
	handle_params(&params, ft_atoi(argv[1]), ft_atoll(argv[2]), ft_atoll(argv[3]), ft_atoll(argv[4]), meals_arg);
	printf("total philo= %d\nto die= %lld\nto eat = %lld\nto sleep = %lld\ntotal meals = %d\n", params->total_philo, params->time_to_die, params->time_to_eat, params->time_to_sleep, params->total_meals);
	init_list(&philo_list);
	while (++i <= params->total_philo)
	{
		push_philo(philo_list, create_philo(i, params->time_to_die, params->time_to_eat, params->time_to_sleep));
	}
	
	free(params);
	t_philo_list *tmp;
	while (philo_list->next)
	{
		tmp = philo_list->next;
		free(philo_list->curr_philo);
		philo_list->curr_philo = tmp->curr_philo;
		philo_list->next = tmp->next;
	}
	free(philo_list);
	return (0);
}

// check arguments (3 mandatory and one optional) argc == 4 || 5 (EXIT CASE)
	// number of philosophers: also the number of forks
	// time to die (milliseconds) (CASE STOP)
	// time to eat (millisconds)
	// time to sleep (milliseconds)
	// [ optional ] number of times each philosophers must eat (CASE STOP)
