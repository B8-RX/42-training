NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread

CFLAGS += -fsanitize=thread

PHILO_LIB = ./philo.h

SRC = philo.c \
    utils.c \
		threads.c \
		monitoring.c \
		checks.c \
		actions.c \
		data_structure.c \
		data_utils.c \

OBJS_PATH = ./objs/

OBJS = $(patsubst %.c, ${OBJS_PATH}%.o, $(notdir ${SRC}))

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< 

all: $(NAME)
        
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -I${PHILO_LIB} -o $(NAME) $(OBJS)
	echo "\033[1mCOMPILATION COMPLETE\033[0m"

${OBJS_PATH}%.o : %.c
	mkdir -p ${OBJS_PATH}
	$(CC) $(CFLAGS) -c -o $@ $< -I$(PHILO_LIB)

clean:
	rm -rf $(OBJS_PATH)
	echo "clean done"

fclean: clean
	rm -rf $(NAME)
	echo "fclean done"

re: fclean all

.PHONY: all, clean, fclean, re

.SILENT:
