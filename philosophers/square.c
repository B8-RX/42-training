#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void	*square(void *arg)
{
	int nbr = *((int *)arg);
	int *result = malloc (sizeof(nbr));

	*result = nbr * nbr;
	return ((void *)result);
}

int main(void)
{
	pthread_t	t1, t2;
	int			nombre1, nombre2;
	int			*result1, *result2;

	nombre1 = 5;
	nombre2 = 10;
	pthread_create(&t1, NULL, &square, &nombre1);
	pthread_create(&t2, NULL, &square, &nombre2);
	
	pthread_join(t1, (void **)&result1);
	pthread_join(t2, (void **)&result2);

	printf("square of %d equal %d\n", nombre1, *result1);
	printf("square of %d equal %d\n", nombre2, *result2);
	
	free(result1);
	free(result2);
	return (0);
}

