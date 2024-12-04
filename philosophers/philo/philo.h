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


typedef struct s_philo_list t_philo_list;

typedef struct s_params
{
	int			total_philo;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
	int			max_meals;
	long long	timestamp_start;
	bool		a_philo_died;
	bool		all_finished;
	bool		ready;
	pthread_t	monitor_thread;
	t_philo_list	*philo_list;	
	pthread_mutex_t	*fork;
	pthread_mutex_t	meals_lock;
	pthread_mutex_t	satiate_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	ready_lock;

}	t_params;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	t_params		*params;
	long long		last_meal_timestamp;
	pthread_mutex_t last_meal_lock;
	int				meals_eaten;
	bool			is_ready;
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
t_params	*set_params(char **argv, int max_meals);
void		init_params_mutex(t_params *params);

void		init_philo(t_params *params);
t_philo		*create_philo(int id, t_params *params);
void		create_philos_thread(t_params *params);
void		create_monitor_thread(t_params *params);
void		init_wait_threads(t_params *params);
void		push_philo(t_philo *philo, t_params *params);

void		init_forks(t_params *params);
bool		get_ready(t_params *params);
void		*monitor(void *arg);
bool		monitor_check_stop_cases(t_philo *philo);
bool		found_stop_cases(t_philo *philo);
bool		found_philo_died(t_philo *philo);
bool		is_philo_starve(t_params *params);
bool		all_philo_satiate(t_params *params);

void		log_action(const char *action, t_philo *philo);
void		go_sleep(t_philo *philo);

void		handle_single_philo(t_philo_list *list);
void		handle_forks(t_philo *philo);
int			routine(void *arg);

void		clean_mutex(t_params *params, int mutex_forks, int mutex_meals);
void		clean_data(t_params *params);
void		set_ready(t_params *params);
void	ft_usleep(t_philo *philo, long long milli);
void	free_philo_list(t_philo_list *list);

#endif // !PHILO_H
