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

#include <stdio.h>
#include <stdlib.h>

typedef struct car 
{
	char	*type;
	char	*brand;
	char	*model;
	int		release;
} type_car ;

typedef struct collection 
{
	type_car	*car;
	struct collection	*next;
} cars_book ;

cars_book	*ft_init_cars_book(void)
{
	cars_book	*list_book;
	
	list_book = malloc(sizeof(cars_book));
	if (!list_book)
		return (NULL);
	else
		list_book -> next = NULL;
	return (list_book);
}

cars_book	*ft_add_car_front_book(cars_book **my_collection, type_car *new_car)
{
	cars_book	*new_data;
	
	new_data = malloc(sizeof(cars_book));
	if (!new_data)
		return (NULL);
	else
	{
		new_data -> car = new_car;
		new_data -> next = *my_collection;
		*my_collection = new_data;
	}
	return (*my_collection);
}

void	ft_print_cars(cars_book *collection)
{
	cars_book	*current;
	int			i;

	i = 1;
	current = collection;
	while (current -> next)
	{
		printf("Car %d\ntype:\t%s\nbrand:\t%s\nmodel:\t%s\nrelease\t%d\n\n", i, current -> car -> type, current -> car -> brand, current -> car -> model, current -> car -> release);
		current = current -> next;
		i++;
	}
}

int main(void)
{
	type_car	model_city_1 = 
	{
		"citadine",
		"fiat",
		"panda",
		2023
	};
	type_car	model_sport_1;
	
	model_sport_1.type = "spotive";
	model_sport_1.brand = "Ferrari";
	model_sport_1.model = "Enzo";
	model_sport_1.release = 1986;

	cars_book *my_collection = ft_init_cars_book();	
	
	ft_add_car_front_book(&my_collection, &model_sport_1);
	ft_add_car_front_book(&my_collection, &model_city_1);
	ft_print_cars(my_collection);
	return (0);
}
