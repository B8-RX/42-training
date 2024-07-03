
ifeq ($(shell uname), Linux)
	INCLUDES = -I/usr/include -I../../mlx -Ignl
	MLX_FLAGS = -L../../mlx -lmlx -L/usr/lib/X11 -lXext -lX11
else
	INCLUDES = -I/opt/X11/include -I../../mlx -Ignl
	MLX_FLAGS = -L../../mlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif
 
MLX_DIR = ../../mlx
MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a


GNL_PATH = ./gnl/
GNL_LIB = ./gnl/get_next_line.h

OBJS_PATH = ./objs/

vpath %.c ./ $(GNL_PATH)

SOURCE = ./main.c 
SOURCE_GNL =  ${GNL_PATH}get_next_line.c ${GNL_PATH}get_next_line_utils.c

OBJS = $(patsubst %.c, ${OBJS_PATH}%.o, $(notdir ${SOURCE}))
OBJS_GNL = $(patsubst %.c, ${OBJS_PATH}%.o, $(notdir ${SOURCE_GNL}))

NAME = minilibx_test

CFLAGS = -Wall -Werror -Wextra

CC = cc

all: $(NAME)
 
$(NAME): $(OBJS) $(OBJS_GNL) $(MLX_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(OBJS_GNL) $(MLX_FLAGS)

${OBJS_PATH}%.o : %.c
	mkdir -p ${OBJS_PATH}
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)
 
$(MLX_LIB):
	@make -C $(MLX_DIR) --no-print-directory

clean: 
	rm -rf ${OBJS_PATH}
	cd ${MLX_DIR} && make clean

fclean: clean
	rm -f ${NAME}
	cd ${MLX_DIR} && make clean

re: fclean all

.PHONY : all clean fclean re libft mlx
