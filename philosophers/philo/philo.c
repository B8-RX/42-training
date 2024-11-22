#include "./philo.h"

int main(int argc, char **argv) {
	t_params		  *params;
	t_philo_list	*philo_list;
  t_shared      *shared;

  params = handle_args(argc, argv);
  shared = init_shared(params);
  init_forks(params, shared);
  init_philo(params, &philo_list, shared);
	create_threads(philo_list);
  clean_mutex(params, shared);
  clean_data(shared, philo_list, params);
	return (0);
}
