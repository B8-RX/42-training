#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#ifndef PHILO_H
# define PHILO_H 

typedef struct s_params
{
	int				total_philo;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				total_meals;
} t_params;

typedef struct s_philo
{
	int				id;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		time_to_die;
	bool			eat;
	bool			sleep;
	bool			dead;
	pthread_mutex_t	mutex;
	
} t_philo;

typedef struct s_philo_list
{
	t_philo				*curr_philo;
	struct s_philo_list	*next;
} t_philo_list;

long long	ft_atoll(char *num);
int			ft_atoi(char *num);
size_t		ft_strlen(char *str);

#endif // !PHILO_H

