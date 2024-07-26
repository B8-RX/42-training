# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssghioua <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/18 03:12:38 by ssghioua          #+#    #+#              #
#    Updated: 2023/11/22 23:58:39 by ssghioua         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	  ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	  ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	  ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
	  ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
          ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	  ft_split.c ft_strmapi.c ft_striteri.c ft_strtrim.c ft_itoa.c \
	  get_next_line.c\
	  
SRC_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	    ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
	    ft_lstmap.c

NAME = libft.a

CCFLAGS = cc -Wall -Wextra -Werror

HEADER = libft.h

OBJS_PATH = ./objs/

OBJS = $(patsubst %.c, ${OBJS_PATH}%.o, $(notdir ${SOURCE}))

SRC_ALL = ${SOURCES} ${SRC_BONUS}

OBJS_ALL = $(patsubst %.c, ${OBJS_PATH}%.o, $(notdir ${SRC_ALL}))

all : ${NAME}

${OBJS_PATH}%.o : %.c
	mkdir -p ${OBJS_PATH}
	$(CC) $(CFLAGS) -c -o $@ $< -I$(HEADER)

${NAME} :	${OBJS}
		ar -rsc ${NAME} ${OBJS}

clean :
		rm -f ${OBJS_ALL}

fclean :	clean
		rm -f ${NAME} 

re :		fclean all

bonus :		${OBJS_ALL}
		ar -rsc ${NAME} ${OBJS_ALL}
so:
	-fPIC $(CCFLAGS) $(SRC_ALL)
	gcc -shared -o libft.so $(OBJ_ALL)

.PHONY : all clean fclean re libft mlx
