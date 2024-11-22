#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/time.h>
#include <errno.h>

#ifndef PHILO_H
# define PHILO_H 

typedef struct s_params
{
	int				      total_philo;
  int             total_philo_finished_meals;
	long long		    time_to_die;
	long long	    	time_to_eat;
	long long		    time_to_sleep;
	int				      max_meals;
	long long		    timestamp_start;
  bool            a_philo_died;
  bool            all_finished;
} t_params;

typedef struct s_shared
{
  pthread_mutex_t *fork;
  pthread_mutex_t meals_mutex;
  pthread_mutex_t write_lock;
} t_shared;

typedef struct s_philo
{
	int			  	    id;
  pthread_t       thread;
  t_params        *params;
  t_shared        *shared;
  long long       last_meal_timestamp;
  int             meals_eaten;
  bool            finished_meals;
} t_philo;

typedef struct s_philo_list
{
	t_philo				*curr_philo;
	struct s_philo_list	*next;
} t_philo_list;

typedef enum 
{
  DEAD,
  EAT,
  SLEEP
} t_state;

long long	    ft_atoll(char *num);
int			      ft_atoi(char *num);
size_t	      ft_strlen(char *str);
t_params      *handle_args(int argc, char **argv);
void          set_params(t_params *params, int total_philo, long long time_to_die,
                   long long time_to_eat, long long time_to_sleep, int meals);
bool          is_digits(char *arg);
t_shared      *init_shared(t_params *params);
void          init_forks(t_params *params, t_shared *shared);
void          init_philo(t_params *params, t_philo_list **philo_list, t_shared *shared);
void          init_philo_thr(t_philo_list *list, int *list_length);
void          push_philo(t_philo_list **list, t_philo *philo);
t_philo       *create_philo(int id, t_params *params);
long long     get_timestamp(void);
void          create_threads(t_philo_list *list);
bool  found_stop_cases(t_philo *philo);
bool  found_philo_died(t_philo *philo);
bool  is_philo_starve(t_philo *philo);
bool  all_philo_satiate(t_philo *philo);
bool  monitor_check_stop_cases(t_philo *philo);
void  clean_mutex(t_params *params, t_shared *shared);
void  clean_data(t_shared *shared, t_philo_list *philo_list, t_params *params);
void  handle_single_philo(t_philo_list *list);
void  release_forks(t_philo *philo);
void  log_action(const char *action, t_philo *philo);
void  go_eat(t_philo *philo);
void  go_sleep(t_philo *philo);
void  go_die(t_philo *philo);
bool  handle_forks(t_philo  *philo);
void  *monitor(void *arg);
int  routine(void *arg);

#endif // !PHILO_H

