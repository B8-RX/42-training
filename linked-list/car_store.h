
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef CAR_STORE_H
# define CAR_STORE_H

typedef struct Car 
{
	char	*type;
	char	*brand;
	char	*model;
	int		release;
	char	*id;	
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
char		*ft_get_id(void);
int			ft_check_id_exist(Cars_list *cars_register, char *id);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

#endif // !CAR_STORE_H
