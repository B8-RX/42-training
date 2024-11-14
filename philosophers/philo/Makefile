NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread -O3 -g3

CFLAGS += -fsanitize=thread

PHILO_LIB = ./philo.h

SRC = philo.c \
    utils.c \
		philo_action.c \
		philo_data_management.c \
		routine.c \
		init.c \

OBJS = $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< 

all: $(NAME)
        
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -I${PHILO_LIB} -o $(NAME) $(OBJS)
	echo "\033[1mLets Do It\033[0m"

clean:
	rm -rf $(OBJS)
	echo "ya foy"

fclean: clean
	rm -rf $(NAME)
	echo "c'est fclean gros"

re: fclean all

.PHONY: all, clean, fclean, re

.SILENT:
