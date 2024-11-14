#include "./philo.h"

void  init_philo(t_params *params, t_philo_list **philo_list, t_shared *shared)
{
	int				    i;
	t_philo			  *philo;
	
  i = -1;
  *philo_list = NULL;
  while (++i < params->total_philo)
	{
		philo = create_philo(i, params);
    philo->shared = shared;
		push_philo(philo_list, philo);
	}
}

t_philo	*create_philo(int id, t_params *params) {
	t_philo   *philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
  philo->params = params;
	philo->dead = false;
	philo->eat = false;
	philo->sleep = false;
  philo->meals_eaten = 0;
  return (philo);
}

void push_philo(t_philo_list **list, t_philo *philo) {
	t_philo_list	*new_node;
	t_philo_list	*current;

	new_node = malloc(sizeof(t_philo_list));
	if (!new_node)
		return ;
	new_node->curr_philo = philo;
	new_node->next = NULL;
	if (!*list)
		*list = new_node;
	else
	{
		current = *list;
		while (current->next != NULL)
		  current = current->next;
		current->next = new_node;
	}
}

void	free_philo_list(t_philo_list *list)
{
	t_philo_list *tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->curr_philo);
		free(tmp);
	}
}

void  log_action(const char *action, t_philo *philo)
{
    printf("%lld %d %s\n", (get_timestamp() - philo->params->timestamp_start), philo->id + 1, action);
}

void  set_state(t_philo *philo, t_state state)
{
  pthread_mutex_lock(&philo->shared->write_lock);
  philo->dead = (state == DEAD);
  philo->eat = (state == EAT);
  philo->sleep = (state == SLEEP);
  if (state == EAT)
  {
    philo->meals_eaten += 1;
    if (philo->params->max_meals > 0 && philo->params->max_meals == philo->meals_eaten)
      philo->shared->total_philo_finished_meals += 1;
  }
  pthread_mutex_unlock(&philo->shared->write_lock);
}
