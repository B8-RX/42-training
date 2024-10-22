
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct s_philo
{
	int				id;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		time_to_die;
	bool			eat;
	bool			sleep;
	bool			dead;
	int				nb_of_meals;
	pthread_mutex_t	mutex;
	
} t_philo;

typedef struct s_philo_list
{
	t_philo				philo_data;
	struct s_philo_list	*next;
} t_philo_list;

size_t	ft_strlen(char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

long long	atoll(char *num)
{
	long long	sum;

	sum = 0;
	while (*num && (*num >= 48 && *num <= 57))
	{
		sum = sum * 10 + (*num - '0');
		num++;
	}
	return (sum);
}

int	create_philo(int id, long long time_to_die, long long time_to_eat, long long time_to_sleep, void *meals_arg)
{
	t_philo			philo;

	philo.id = id;
	philo.time_to_die = time_to_die;
	philo.time_to_eat = time_to_eat;
	philo.time_to_sleep = time_to_sleep;
	philo.sleep = false;
	philo.eat = false;
	philo.dead = false;
	

	return (0);
}

int main(int argc, char **argv)
{
	int		i;
	void	*meals_arg;

	i = 0;
	meals_arg = NULL;
	if (argc != 4 && argc != 5)
	{
		printf("ERROR ARGUMENTS\n");
		exit(1);
	}
	if (argc == 5 && argv[4] != 0)
		meals_arg = argv[4];
	while (++i <= atoll(argv[1]))
		create_philo(i, atoll(argv[2]), atoll(argv[3]), atoll(argv[4]), meals_arg);

	return (0);
	// check arguments (3 mandatory and one optional) argc == 4 || 5 (EXIT CASE)
	// number of philosophers: also the number of forks
	// time to die (milliseconds) (CASE STOP)
	// time to eat (millisconds)
	// time to sleep (milliseconds)
	// [ optional ] number of times each philosophers must eat (CASE STOP)
}
