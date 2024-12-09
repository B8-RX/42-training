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
	int			total_philo_finished_meals;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
	int			max_meals;
	long long	timestamp_start;
	bool		a_philo_died;
	bool		all_finished;
	t_philo_list	*philo_list;	
	pthread_mutex_t	*fork;
	pthread_mutex_t	meals_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	display_lock;
}	t_params;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	t_params	*params;
	long long	last_meal_timestamp;
	int			meals_eaten;
	bool		finished_meals;
}	t_philo;

typedef struct s_philo_list
{
	t_philo				*curr_philo;
	struct s_philo_list	*next;
}	t_philo_list;

int			ft_atoi(const char *num);
size_t		ft_strlen(char *str);
bool		is_digits(char *arg);
long long	get_timestamp(void);

t_params	*handle_args(int argc, char **argv);
bool	is_valid_args(t_params *params, int argc, char **argv);
t_params	*set_data(char **argv, int max_meals);
void		init_shared_mutex(t_params *params);

void		init_philo(t_params *params);
t_philo		*create_philo(int id, t_params *params);
int			create_threads(t_params *params);
void		add_philo_list(t_philo *philo, t_params *params);
void	free_philo_list(t_philo_list *list);

void		create_monitor_threads(t_philo_list *list);
void		init_forks_mutex(t_params *params);

void		*monitor(void *arg);
bool		monitor_check_stop_cases(t_philo *philo);
bool		found_stop_cases(t_philo *philo);
bool		is_philo_starve(t_philo *philo);
bool		all_philo_satiate(t_philo *philo);

void		log_action(const char *action, t_philo *philo);
void		go_eat(t_philo *philo, int left_fork, int right_fork);
void		go_sleep_think(t_philo *philo);
void		ft_usleep(t_philo *philo, long long pause);
void		go_die(t_philo *philo);

void		handle_single_philo(t_philo_list *list);
bool		handle_forks(t_philo *philo);
void		*routine(void *arg);

void		clean_mutex(t_params *params, int fork_mutex);
void		clean_data(t_params *params);
void		release_forks(t_philo *philo);
bool		all_are_ready(t_params *params);

#endif // !PHILO_H
