
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef CAR_STORE_H
# define CAR_STORE_H

	

typedef struct Car 
{
	char	*type;
	char	*brand;
	char	*model;
	int		release;
} Car_model ;

typedef struct Collection 
{
	Car_model	*car;
	struct Collection	*next;
} Cars_list ;



Cars_list	*ft_add_car_front(Cars_list **cars_register, Car_model *new_car);
Cars_list	*ft_add_car_back(Cars_list **cars_register, Car_model *new_car);
Cars_list	*ft_init_cars_register(void);
void		ft_print_cars(Cars_list *collection);
void		ft_free_cars_list(Cars_list *cars_register);

#endif // !CAR_STORE_H
