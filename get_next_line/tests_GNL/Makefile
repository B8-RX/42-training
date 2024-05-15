# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/19 02:40:49 by ssghioua          #+#    #+#              #
#    Updated: 2023/12/19 02:40:55 by ssghioua         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

define PURGE
$(if $(2),$(call PURGE,$(subst $(firstword $(2)),,$(1)),$(filter-out $(firstword $(2)),$(2))),$(1))
endef

DIGITS := 0 1 2 3 4 5 6 7 8 9
define IS_NOT_A_NUMBER
$(call PURGE,$(1),$(DIGITS))
endef


SOURCES = main.c

SOURCES_PATH = ../gnl_v3_bonus_linked_list/

SOURCES_GNL = ${wildcard ${SOURCES_PATH}*_bonus.c} 

NAME = output_test_gnl.a

CCFLAGS = cc -Wall -Werror -Wextra

BUFFER_SIZE = 1

OBJECTS = ${SOURCES:.c=.o}

OBJECTS_GNL = $(pathsubst ${SOURCES_GNL:${SOURCES_PATH}%.c=${SOURCES_PATH}%.o})

HEADER = ${SOURCES_PATH}get_next_line_bonus.h

CCFLAGS += $(if $(call IS_NOT_A_NUMBER,$(BUFFER_SIZE)),,-D BUFFER_SIZE=$(BUFFER_SIZE))

all :	${NAME}
	$(info BUFFER_SIZE=$(BUFFER_SIZE) => CCFLAGS=$(CCFLAGS))

${SOURCES_PATH}%.o : ${SOURCES_PATH}%.c
	${CCFLAGS} -I ${HEADER} -c $< -o $@

${NAME} :	${OBJECTS_GNL} ${OBJECTS} 
	ar -rsc ${NAME} ${OBJECTS} ${SOURCES_PATH}${OBJECTS_GNL}
		${CCFLAGS} ${NAME} -o run_test_gnl

${OBJECTS_GNL} :
	${CCFLAGS} -c ${SOURCES_GNL}
	mv ./*.o ../gnl_v3_bonus_linked_list/

clean :
	rm -f ${OBJECTS} ${OBJECTS_GNL}

fclean :	clean
	rm -f ${NAME} run_test_gnl

re : fclean all



