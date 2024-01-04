
#include "car_store.h"

Cars_list	*ft_init_cars_register(void)
{
	Cars_list	*list;
	
	list = malloc(sizeof(Cars_list));
	if (!list)
		return (NULL);
	list -> car = NULL;
	list -> next = NULL;
	return (list);
}

Cars_list	*ft_add_car_front(Cars_list **cars_register, Car_model *new_car)
{
	printf("\n\t-----ADD_CAR_FRONT FUNCTION-----\n");
	
	Cars_list	*new_data;
	char		*id;

	id = ft_get_id();
	while (ft_check_id_exist(*cars_register, id))
	{
		printf("ID: %s ALREADY EXIST\n", id);
		printf("GENERATE NEW ID\n");
		id = ft_get_id();
		printf("NEW ID: %s\n", id);
	}
	printf("UNIQUE ID GENERATED\n");
	new_car -> id = id;
	new_data = malloc(sizeof(Cars_list));
	if (!new_data)
		return (NULL);
	new_data -> car = new_car;
	new_data -> next = *cars_register;
	*cars_register = new_data;
	printf("car: %s %s id:%s\tADDED\n\n", new_data -> car -> brand, new_data -> car -> model, new_data -> car -> id);
	return (new_data);
}

void	ft_print_cars(Cars_list *cars_register)
{
	printf("\n\t-----PRINT_CARS FUNCTION-----\n");

	int	i;

	if (cars_register == NULL)
	{
		printf("the list is empty\n");
		return ;
	}
	i = 1;
	do
	{
		printf("\ncar %d\ntype: %s\nbrand: %s\nmodel: %s\nrelease: %d\nid: %s\n\n", i, cars_register -> car -> type, cars_register->car->brand, cars_register -> car -> model, cars_register -> car -> release, cars_register -> car -> id);
		cars_register = cars_register -> next;
		i++;
    }
	while (cars_register != NULL);
}

Cars_list	*ft_add_car_back(Cars_list **cars_register, Car_model *new_car)
{
	printf("\n\t-----ADD_CAR_BACK FUNCTION-----\n");

	Cars_list	*current;
 	char		*id;

	id = ft_get_id();
	while (ft_check_id_exist(*cars_register, id))
	{
		printf("ID: %s ALREADY EXIST\n", id);
		printf("GENERATE NEW ID\n");
		id = ft_get_id();
		printf("NEW ID: %s\n", id);
	}
	printf("UNIQUE ID GENERATED\n");

	new_car -> id = id;
	if ((*cars_register) -> car == NULL)
	{
		(*cars_register) -> car = new_car;
		(*cars_register) -> next = NULL;
    } 
	else
	{
        current = *cars_register;
        while (current->next != NULL)
        {
            current = current->next;
        }
		current -> car = new_car;
		printf("car: %s %s id: %s\tADDED\n\n", current -> car -> brand, current -> car -> model, current -> car -> id);
        current -> next = NULL;
    }
    return (*cars_register);
}

void	ft_free_cars_list(Cars_list *cars_register)
{
	Cars_list	*temp;
	
	while (cars_register  != NULL)
	{
		temp = cars_register;
		cars_register = cars_register -> next;
		free(temp);
		temp = NULL;
	}
}

char	*ft_get_id(void)
{
	int		i;
	char	*id;
	char hexa[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','\0'};
	
	id = malloc(37 + 1);
	i = 0;
	while (i < 37)
	{
		id[i] = hexa[rand() % 16];
		i++;
	}
	id[8] = '-';
	id[13] = '-';
	id[18] = '-';
	id[23] = '-';
	id[i] = '\0';
	return (id);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_check_id_exist(Cars_list *cars_register, char *id)
{
	printf("\n-----CHECK_ID FUNCTION-----\n");

	if (cars_register && cars_register -> next == NULL)
		return (0);
	while (cars_register && cars_register -> next != NULL)
	{
		if (ft_strncmp((cars_register -> car -> id), id, ft_strlen(id)) == 0)
			return (1);
		cars_register = cars_register -> next;
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*s1 && *s2 && *s1 == *s2 && (n - 1))
	{
		s1++;
		s2++;
		n--;
	}
	if (*s1 != *s2)
		return ((unsigned char)*s1 - (unsigned char)*s2);
	return (0);
}

char	*ft_remove_car_by_id(Cars_list **cars_register, char *car_id)
{
	Cars_list	*last;
	Cars_list	*current;

	printf("\n\t-----REMOVE_CAR FUNCTION-----\n");
	last = *cars_register;
	current = *cars_register;
	if (ft_strncmp(current -> car -> id, car_id, ft_strlen(car_id)) == 0)
	{
		*cars_register = current -> next;
		free(current);
		printf("SUCCESSFULLY REMOVED car_id: %s\n", car_id);
		return (car_id);
	}
	while (*cars_register  != NULL)
	{
		if (ft_strncmp(car_id, current -> car -> id, ft_strlen(car_id)) == 0)
		{
			last -> next = current -> next;
			free(current);
			printf("SUCCESSFULLY REMOVED car_id: %s\n", car_id);
			return (car_id);
		}
		else if (ft_strncmp(car_id, current -> next -> car -> id, ft_strlen(car_id)) != 0)
		{
			current = current -> next;
			last = current;
		}
		else
			current = current -> next;
	}
	return (NULL);
}

char	*ft_strdup(char *src)
{
	char	*new;
	int		i;

	new = (char *)malloc((ft_strlen(src) / sizeof(char)) + 1);
	if (new == NULL)
		return (new);
	i = 0;
	while (src[i])
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
