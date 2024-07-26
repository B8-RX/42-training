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
	Car_model model_city_2_2= {"Citadine", "Tesla", "Model X", 2032, NULL};
	Cars_list *cars_register = ft_init_cars_register();	
	ft_add_car_front(&cars_register, &model_sport_1);
	ft_add_car_front(&cars_register, &model_sport_2);
	ft_add_car_front(&cars_register, &model_city_1);
	ft_add_car_front(&cars_register, &model_city_2);
	ft_add_car_back(&cars_register, &model_sport_3);
/* 	ft_remove_car_by_id(&cars_register, "458e199c-89f5-b135-7091-5abb0874df3e8"); */
	// ft_remove_car_by_id(&cars_register, "83a5d578-e4b2-6b44-e241-dc709e111c7e1");
	// ft_remove_car_by_id(&cars_register, "458e199c-89f5-b135-7091-5abb0874df3e8");
	// ft_remove_car_by_id(&cars_register, "76931fac-dab2-36c2-8b87-6ae33f9a62d71");
	// ft_remove_car_by_id(&cars_register, "e7acb6f8-ac0b-2fc4-8bc2-e3baaab9165cc");
	// ft_update_car_by_id(&cars_register, &model_city_2_2, "458e199c-89f5-b135-7091-5abb0874df3e8"); 
	ft_print_cars(cars_register);
	ft_free_cars_list(cars_register);
	return (0);
}
