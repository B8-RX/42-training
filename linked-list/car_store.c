/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 08:40:48 by ssghioua          #+#    #+#             */
/*   Updated: 2023/11/29 08:40:51 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "car_store.h"

int main(void)
{
	Car_model	model_sport_2 = {"sportive", "Porshe", "911 GT3 RS", 2020};
	Car_model	model_sport_3 = {"sportive", "Lamborgini", "Avantadore", 2022};
	Car_model	model_city_1 =	{"citadine","fiat", "panda", 2023};
	Car_model	model_sport_1 = {"spotive", "Ferrari", "Enzo", 1986};
	
	Cars_list *cars_register = ft_init_cars_register();	
	ft_add_car_front(&cars_register, &model_sport_1);
	ft_add_car_front(&cars_register, &model_sport_2);
	ft_add_car_front(&cars_register, &model_city_1);
	ft_add_car_back(&cars_register, &model_sport_3);
	ft_print_cars(cars_register);
	ft_free_cars_list(cars_register);
	return (0);
}
