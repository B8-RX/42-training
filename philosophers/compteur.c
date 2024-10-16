/* **************************************************************************
 */
/*                                                                            */
/*                                                        :::      :::::::: */
/*   main.c                                             :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+ */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+ */
/*                                                +#+#+#+#+#+   +#+ */
/*   Created: 2024/10/14 01:53:50 by ssghioua          #+#    #+# */
/*   Updated: 2024/10/14 01:53:53 by ssghioua         ###   ########.fr */
/*                                                                            */
/* **************************************************************************
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int compteur = 0;
pthread_mutex_t	mutex;

void *incrementer(void *arg) {

	int i = 0;
	
	while (i++ < 10)
	{
		pthread_mutex_lock(&mutex);
		compteur++;
		printf("%s : compteur = %d\n", (char *)arg, compteur);
		pthread_mutex_unlock(&mutex);
		usleep(100);
	}
	
	return (NULL);
}

int main(int argc, char **argv) {

	pthread_t t1, t2;
	
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&t1, NULL, &incrementer, "thread 1");
	pthread_create(&t2, NULL, &incrementer, "thread 2");

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	pthread_mutex_destroy(&mutex);

	return (0);
}
