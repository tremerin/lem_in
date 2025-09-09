NAME		= lem_in
SRC			= srcs/main.c\
			srcs/parser.c\
			srcs/table_2d.c\
			srcs/multi_str.c\
			srcs/pathfinder.c\
			srcs/ants_movement.c\

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
RM			= rm -f
LIBFT_PATH 	= ./Libft
OBJS		= $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	make -C $(LIBFT_PATH)
	$(CC) $(OBJS) $(LIBFT_PATH)/libft.a -o $(NAME)

clean :
	make -C $(LIBFT_PATH) clean
	$(RM) $(OBJS)

fclean :
	make -C $(LIBFT_PATH) fclean
	$(RM) $(OBJS) $(NAME)

re : fclean all
