/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 03:11:15 by ssghioua          #+#    #+#             */
/*   Updated: 2024/11/23 03:11:16 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H 

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <errno.h>

typedef struct s_params
{
	int			total_philo;
	int			total_philo_finished_meals;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
	int			max_meals;
	long long	timestamp_start;
	bool		a_philo_died;
	bool		all_finished;
}	t_params;

typedef struct s_shared
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	meals_mutex;
	pthread_mutex_t	write_lock;
}	t_shared;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	t_params	*params;
	t_shared	*shared;
	long long	last_meal_timestamp;
	int			meals_eaten;
	bool		finished_meals;
}	t_philo;

typedef struct s_philo_list
{
	t_philo				*curr_philo;
	struct s_philo_list	*next;
}	t_philo_list;

typedef enum e_state
{
	DEAD,
	EAT,
	SLEEP
}	t_state;

long long	ft_atoll(char *num);
int			ft_atoi(char *num);
size_t		ft_strlen(char *str);
bool		is_digits(char *arg);
long long	get_timestamp(void);

t_params	*handle_args(int argc, char **argv);
t_params	*set_params(char **argv, int meals);
t_shared	*init_shared(t_params *params);

void		init_philo_list(t_params *params,
				t_philo_list **list, t_shared *shared);
t_philo		*create_philo(int id, t_params *params);
void		push_philo(t_philo_list **list, t_philo *philo);

void		create_threads(t_philo_list *list);
void		init_philo_thr(t_philo_list *list, int *list_length);
void		init_forks(t_params *params, t_shared *shared);

void		*monitor(void *arg);
bool		monitor_check_stop_cases(t_philo *philo);
bool		found_stop_cases(t_philo *philo);
bool		found_philo_died(t_philo *philo);
bool		is_philo_starve(t_philo *philo, long long last_meal_timestamp);
bool		all_philo_satiate(t_philo *philo, int meals_eaten);

void		log_action(const char *action, t_philo *philo);
void		go_eat(t_philo *philo);
void		go_sleep(t_philo *philo);
void		go_die(t_philo *philo);

void		handle_single_philo(t_philo_list *list);
bool		handle_forks(t_philo *philo);
int			routine(void *arg);

void		clean_mutex(t_params *params, t_shared *shared);
void		clean_data(t_shared *shared, t_philo_list *list, t_params *params);
void		release_forks(t_philo *philo);

#endif // !PHILO_H
