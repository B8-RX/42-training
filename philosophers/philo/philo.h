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
	bool		meals_arg;
	long long	timestamp_start;
	bool		a_philo_died;
	bool		all_finished;
	bool		philos_ready;
}	t_params;

typedef struct s_shared
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	meals_lock;
	pthread_mutex_t	rw_lock;
	pthread_mutex_t	satiate_lock;
	pthread_mutex_t	end_lock;
	pthread_mutex_t launcher_lock;
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

int			ft_atoi(const char *num);
size_t		ft_strlen(char *str);
bool		is_digits(char *arg);
long long	get_timestamp(void);

t_params	*handle_args(int argc, char **argv);
t_params	*set_params(char **argv, bool meals_arg, int max_meals);
t_shared	*init_shared(t_params *params);

void		init_philo_list(t_params *params,
				t_philo_list **list, t_shared *shared);
t_philo		*create_philo(int id, t_params *params);
void		push_philo(t_philo_list **list, t_philo *philo);

void		create_threads(t_philo_list *list, int total_philo);
int			init_philo_thr(t_philo_list *list, int total_philo);
void		init_forks(t_params *params, t_shared *shared);

void		*monitor(void *arg);
bool		monitor_check_stop_cases(t_philo *philo);
bool		found_stop_case(t_philo *philo);
bool		someone_starve(t_philo *philo);
bool		all_philo_satiate(t_philo *philo);

void		log_action(const char *action, t_philo *philo);
void		go_eat(t_philo *philo);
void		go_sleep(t_philo *philo);
void		go_die(t_philo *philo);

void		handle_single_philo(t_philo_list *list);
bool		handle_forks(t_philo *philo);
int			routine(void *arg);

void		clean_mutex(int forks, t_shared *shared);
void		clean_data(t_shared *shared, t_philo_list *list, t_params *params);
void		release_forks(t_philo *philo);

void		set_philos_ready(t_philo *philo);
bool		check_philos_ready(t_philo *philo);

#endif // !PHILO_H
