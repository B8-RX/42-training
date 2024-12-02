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

	params = handle_args(argc, argv);
	init_philo(params);
	init_mutex(params);
	create_monitor_thread(params);
	init_wait_threads(params);	
	clean_mutex(params, params->total_philo, params->total_philo);
	clean_data(params);
	return (0);
}
