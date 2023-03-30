
NAME		= cub3d

CC			= cc
#CFLAGS		= -Wall -Wextra -Werror

RM			= rm -rf

SRCS		= main.c \


OBJS		= $(SRCS:.c=.o)

all:		$(NAME)
			@printf "\033[32m-> Executable Done! <-\033[0m\n"

libft.a:
			@$(MAKE) all -C libft

$(NAME):	libft.a $(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L ./libft -lft

clean:
			@$(RM) $(OBJS)
			@$(MAKE) clean -C libft
			@printf "\033[35m-> *.o cleaned! <-\033[0m\n"

fclean:		clean
			@$(RM) $(NAME)
			@$(MAKE) fclean -C libft
			@printf "\033[36m-> executable deleted! <-\033[0m\n"

re:			fclean all

.PHONY:		all clean fclean re

