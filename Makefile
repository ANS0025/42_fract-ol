NAME = fractol
# INCLUDES = -I/opt/X11/include -Imlx
SRCS = events.c init.c main.c math_utils.c render.c string_utils.c
OBJS = $(SRCS:.c=.o)
MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a
LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
# MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit
LIBFT_FLAGS = -Llibft -lft
# CFLAGS = -Wall -Wextra -Werror
CC = cc
all: $(LIBFT_LIB) $(MLX_LIB) $(NAME)
 
.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $(NAME)  
 
$(MLX_LIB):
	@make -C $(MLX_DIR)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

# TODO: clean and fclean not working. Need to fix
clean:
	rm -f $(OBJS)
	make -C $(MLX_DIR) clean
	make -C $(LIBFT_DIR) clean

fclean: 
	rm -f $(OBJS)
	rm -f $(NAME)
	make -C $(MLX_DIR) fclean
	make -C $(LIBFT_DIR) fclean