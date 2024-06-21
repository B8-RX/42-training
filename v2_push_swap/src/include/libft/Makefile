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

SRC_PATH = ./src/
OBJ_PATH = ./src/obj/

SOURCES = ${SRC_PATH}ft_isalpha.c ${SRC_PATH}ft_isdigit.c ${SRC_PATH}ft_isalnum.c ${SRC_PATH}ft_isascii.c ${SRC_PATH}ft_isprint.c \
	  ${SRC_PATH}ft_strlen.c ${SRC_PATH}ft_memset.c ${SRC_PATH}ft_bzero.c ${SRC_PATH}ft_memcpy.c ${SRC_PATH}ft_memmove.c \
	  ${SRC_PATH}ft_strlcpy.c ${SRC_PATH}ft_strlcat.c ${SRC_PATH}ft_toupper.c ${SRC_PATH}ft_tolower.c ${SRC_PATH}ft_strchr.c \
	  ${SRC_PATH}ft_strrchr.c ${SRC_PATH}ft_strncmp.c ${SRC_PATH}ft_memchr.c ${SRC_PATH}ft_memcmp.c ${SRC_PATH}ft_strnstr.c \
	  ${SRC_PATH}ft_atoi.c ${SRC_PATH}ft_calloc.c ${SRC_PATH}ft_strdup.c ${SRC_PATH}ft_substr.c ${SRC_PATH}ft_strjoin.c \
          ${SRC_PATH}ft_putchar_fd.c ${SRC_PATH}ft_putstr_fd.c ${SRC_PATH}ft_putendl_fd.c ${SRC_PATH}ft_putnbr_fd.c \
	  ${SRC_PATH}ft_split.c ${SRC_PATH}ft_strmapi.c ${SRC_PATH}ft_striteri.c ${SRC_PATH}ft_strtrim.c ${SRC_PATH}ft_itoa.c \
	  
SOURCES_BONUS = ${SRC_PATH}ft_lstnew.c ${SRC_PATH}ft_lstadd_front.c ${SRC_PATH}ft_lstsize.c ${SRC_PATH}ft_lstlast.c \
	    ${SRC_PATH}ft_lstadd_back.c ${SRC_PATH}ft_lstdelone.c ${SRC_PATH}ft_lstclear.c ${SRC_PATH}ft_lstiter.c \
	    ${SRC_PATH}ft_lstmap.c

NAME = libft.a

CCFLAGS = cc -Wall -Wextra -Werror

HEADER = ./src/include/libft.h

OBJECTS = $(patsubst $(SRC_PATH)%.c,$(OBJ_PATH)%.o,$(SOURCES))

OBJECTS_BONUS = $(patsubst $(SRC_PATH)%.c,$(OBJ_PATH)%.o,$(SOURCES_BONUS))

SRC_ALL = ${SOURCES} ${SOURCES_BONUS}

OBJ_ALL = ${OBJECTS} ${OBJECTS_BONUS}

all :		${NAME}

${OBJ_PATH}%.o : ${SRC_PATH}%.c
	@mkdir -p $(@D)
	${CCFLAGS} -I ${HEADER} -c $< -o $@
	
${NAME} :	${OBJECTS}
		ar -rsc ${NAME} ${OBJECTS}

clean :
		rm -f ${OBJ_ALL}

fclean :	clean
		rm -f ${NAME} 

re :		fclean all

bonus :		${OBJ_ALL}
		ar -rsc ${NAME} ${OBJ_ALL}
so:
	-fPIC $(CCFLAGS) $(SRC_ALL)
	gcc -shared -o libft.so $(OBJ_ALL)
