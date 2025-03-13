CC = gcc
CFLAGS = -Wall -Wextra -Werror -fPIC
NAME = fdf
SRCS = src/main.c src/events.c src/parser.c src/render.c src/get_color.c src/free_memory.c src/utils/utils_render.c src/utils/utils_parser.c gnl/get_next_line.c gnl/utils.c
OBJS = $(SRCS:.c=.o)
MLX = minilibx
MLX_FLAGS = -L$(MLX) -lmlx -lX11 -lXext -lm -no-pie
LIBFT = libft

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX_FLAGS) -L$(LIBFT) -lft

$(LIBFT):
	make -C $(LIBFT)

clean:
	rm -f $(OBJS)
	@make -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT) clean

re: fclean all

.PHONY: all clean fclean re libft