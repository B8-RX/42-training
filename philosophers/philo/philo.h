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
	long long		    time_to_die;
	long long	    	time_to_eat;
	long long		    time_to_sleep;
	int				      max_meals;
  bool            limit_meals_reach;
} t_params;

typedef struct s_shared
{
  pthread_mutex_t *fork;
  pthread_mutex_t meals_mutex;
  int             total_philo_finished_meals;
} t_shared;

typedef struct s_philo
{
	int			  	    id;
  pthread_t       thread;
  t_params        *params;
  t_shared        *shared;
	bool		      	dead;
	bool  		    	eat;
	bool	  	    	sleep;
  long long       timestamp_meal;
  long long       time_since_last_meal;
  int             meals_eaten;
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
int           lock_fork(pthread_mutex_t *fork);
int           unlock_fork(pthread_mutex_t *fork);
t_params      *handle_args(int argc, char **argv);
void          set_params(t_params *params, int total_philo, long long time_to_die,
                   long long time_to_eat, long long time_to_sleep, int meals);
bool          is_digits(char *arg);
t_shared      *init_shared(t_params *params);
void          init_forks(t_params *params, t_shared *shared);
void          init_philo(t_params *params, t_philo_list **philo_list, t_shared *shared);
void          push_philo(t_philo_list **list, t_philo *philo);
t_philo       *create_philo(int id, t_params *params);


#endif // !PHILO_H

