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

void *routine() {
  printf("Test from treads\n");
  sleep(3);
  printf("End of threads\n");
  return (NULL);
}

int main(int argc, char **argv) {

  pthread_t t1, t2;

  if (pthread_create(&t1, NULL, &routine, NULL) != 0) {
    return 1;
  }
  if (pthread_create(&t2, NULL, &routine, NULL) != 0) {
    return 2;
  }
  if (pthread_join(t1, NULL) != 0) {
    return 3;
  }
  if (pthread_join(t2, NULL) != 0) {
    return 4;
  }
  return (0);
}
