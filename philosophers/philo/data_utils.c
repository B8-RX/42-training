/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 04:18:00 by ssghioua          #+#    #+#             */
/*   Updated: 2024/11/22 04:18:01 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

t_params	*handle_args(int argc, char **argv)
{
	int			meals_arg;
	t_params	*params;

	meals_arg = -1;
	if (argc != 5 && argc != 6)
	{
		fprintf(stderr, "ERROR ARGUMENTS\n");
		exit (1);
	}
	if (argc == 6 && argv[5] && is_digits(argv[5]) && ft_atoi(argv[5]) > 0)
		meals_arg = ft_atoi(argv[5]);
	params = set_params(argv, meals_arg);
	if (params->total_philo <= 0 || params->total_philo > 200)
	{
		free(params);
		fprintf(stderr, "PHILOS SHOULD BE BETWEEN 1 AND 200\n");
		exit (1);
	}
	return (params);
}

void	free_philo_list(t_philo_list *list)
{
	t_philo_list	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->curr_philo);
		free(tmp);
	}
}

void	clean_data(t_shared *shared, t_philo_list *philo_list, t_params *params)
{
	free(shared->fork);
	free(shared);
	free_philo_list(philo_list);
	free(params);
}

void	clean_mutex(t_params *params, t_shared *shared)
{
	int	i;

	i = -1;
	while (++i < params->total_philo)
		pthread_mutex_destroy(&shared->fork[i]);
	pthread_mutex_destroy(&shared->write_lock);
}
