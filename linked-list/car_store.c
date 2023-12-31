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
	Car_model	model_sport_1;
	Car_model	model_sport_2 = {"sportive", "Porshe", "911 GT3 RS", 2020};
	Car_model	model_city_1 = 
	{
		"citadine",
		"fiat",
		"panda",
		2023
	};

	
	model_sport_1.type = "spotive";
	model_sport_1.brand = "Ferrari";
	model_sport_1.model = "Enzo";
	model_sport_1.release = 1986;
	
	Cars_list *register_cars = ft_init_cars_register();	
	ft_add_car_front(&register_cars, model_sport_1);
	ft_add_car_front(&register_cars, model_city_1);
	ft_add_car_front(&register_cars, model_sport_2);
	ft_print_cars(register_cars);
	return (0);
}
