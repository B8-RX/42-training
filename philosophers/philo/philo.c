/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 03:10:44 by ssghioua          #+#    #+#             */
/*   Updated: 2024/11/23 03:10:45 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	main(int argc, char **argv)
{
	t_params		*params;
	t_philo_list	*philo_list;
	t_shared		*shared;

	params = handle_args(argc, argv);
	shared = init_shared(params);
	init_forks(params, shared);
	init_philo_list(params, &philo_list, shared);
	create_threads(philo_list);
	clean_mutex(params->total_philo, shared);
	clean_data(shared, philo_list, params);
	return (0);
}
