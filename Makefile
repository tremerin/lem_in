NAME		= lem_in
NAME_B		= visualizer
SRC			= srcs/main.c\
			srcs/parser.c\
			srcs/table_2d.c\
			srcs/multi_str.c\
			srcs/pathfinder.c\
			srcs/ants_movement.c\

BONUS		= srcs/visualizer.c

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
RM			= rm -f
LIBFT_PATH 	= ./Libft
OBJS		= $(SRC:.c=.o)
OBJS_B		= ${BONUS:.c=.o}
HEADERS		= -I include -I $(MLX42)
LIBS		= $(MLX42)/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	make -C $(LIBFT_PATH)
	$(CC) $(OBJS) $(LIBFT_PATH)/libft.a -o $(NAME)

bonus:	${OBJS_B}
	$(CC) $(OBJS_B) $(HEADERS) $(LIBS) -o $(NAME_B)

clean :
	make -C $(LIBFT_PATH) clean
	$(RM) $(OBJS) $(OBJS_B)

fclean :
	make -C $(LIBFT_PATH) fclean
	$(RM) $(OBJS) $(OBJS_B) $(NAME) $(NAME_B)

re : fclean all
