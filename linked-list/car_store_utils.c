
#include "car_store.h"

Cars_list	*ft_init_cars_register(void)
{
	Cars_list	*list_book;
	
	list_book = malloc(sizeof(Cars_list));
	if (!list_book)
		return (NULL);
	else
		list_book -> next = NULL;
	return (list_book);
}

Cars_list	*ft_add_car_front(Cars_list **register_cars, Car_model new_car)
{
	Cars_list	*new_data;
	
	new_data = malloc(sizeof(Cars_list));
	if (!new_data)
		return (NULL);
	else
	{
		new_data -> car = malloc(sizeof(Car_model));
		if (!new_data -> car)
		{
			free(new_data);
			return (NULL);
		}
		*(new_data -> car) = new_car;
		new_data -> next = *register_cars;
		*register_cars = new_data;
	}
	return (new_data);
}

void	ft_print_cars(Cars_list *register_cars)
{
	Cars_list	current;
	int			i;

	i = 1;
	current = *register_cars;
	while (current.next)
	{
		printf("Car %d\ntype:\t%s\nbrand:\t%s\nmodel:\t%s\nrelease:\t%d\n\n", i, current.car ->type, current.car -> brand, current.car -> model, current.car -> release);
		current = *current.next;
		i++;
	}
}

// Cars_list	ft_add_car_back(Cars_list **register_cars, )
