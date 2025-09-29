NAME		= lem_in
NAME_B		= visualizer
NAME_C		= checker

SRC			= srcs/main.c\
			srcs/parser.c\
			srcs/table_2d.c\
			srcs/multi_str.c\
			srcs/pathfinder.c\
			srcs/ants_movement.c\

BONUS		= bonus/main.c\
			bonus/parser.c\
			bonus/shapes.c\
			bonus/instruction.c\
			bonus/hooks.c\

CHECKER		= checker.c

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
RM			= rm -f
LIBFT_PATH 	= ./Libft
MLX42_PATH  = ./MLX42
OBJS		= $(SRC:.c=.o)
OBJS_B		= ${BONUS:.c=.o}
OBJS_C		= ${CHECKER:.c=.o}
HEADERS		= -I $(MLX42_PATH)/MLX42.h
LIBS		= $(MLX42_PATH)/libmlx42.a -ldl -lglfw -pthread -lm

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	make -C $(LIBFT_PATH)
	$(CC) $(OBJS) $(LIBFT_PATH)/libft.a -o $(NAME)

bonus:	${OBJS_B}
	make -C $(LIBFT_PATH)
	$(CC) $(OBJS_B) $(LIBS) $(LIBFT_PATH)/libft.a -o $(NAME_B)

checker: ${OBJS_C}
	make -C $(LIBFT_PATH)
	$(CC) $(OBJS_C) $(LIBFT_PATH)/libft.a -o $(NAME_C)

clean :
	make -C $(LIBFT_PATH) clean
	$(RM) $(OBJS) $(OBJS_B)

fclean :
	make -C $(LIBFT_PATH) fclean
	$(RM) $(OBJS) $(OBJS_B) $(NAME) $(NAME_B)

re : fclean all
