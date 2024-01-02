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

	Car_model	model_sport_2 = {"Sportive", "Porshe", "911 GT3 RS", 2022, NULL};
	Car_model	model_sport_3 = {"Sportive", "Lamborgini", "Avantadore", 2011, NULL};
	Car_model	model_city_1 =	{"Citadine", "Fiat", "Panda", 1990, NULL};
	Car_model	model_sport_1 = {"Spotive", "Ferrari", "Enzo", 2002, NULL};
	Car_model	model_city_2 =  {"Citadine", "Tesla", "Cybertruck", 2023, NULL};
	
	srand(time(NULL));
	Cars_list *cars_register = ft_init_cars_register();	
	ft_add_car_front(&cars_register, &model_sport_1);
	ft_add_car_front(&cars_register, &model_sport_2);
	ft_add_car_front(&cars_register, &model_city_1);
	ft_add_car_back(&cars_register, &model_sport_3);
	ft_add_car_front(&cars_register, &model_city_2);
	ft_print_cars(cars_register);
	ft_free_cars_list(cars_register);
	return (0);
}
