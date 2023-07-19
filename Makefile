NAME		= minishell
CC			= gcc
CFLAGS		=  -Wall -Wextra -Werror -g
RM			= rm -f
SRCS	=	main.c utils.c pipes/pipes.c env/set_env.c builtin/builtin.c builtin/echo.c builtin/utils.c
OBJS = $(SRCS:.c=.o)
LIBFT       = libft.a
LIBFT_DIR := libft
LIBFT_LIB := $(LIBFT_DIR)/$(LIBFT)

.c.o:
		$(CC) $(CFLAGS) -c $< -o $@ 

all:	$(NAME)

$(LIBFT_LIB):
	@cd $(LIBFT_DIR) && $(MAKE) --silent

$(NAME):	$(OBJS) $(LIBFT_LIB)
			$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -o $(NAME) -lreadline

clean:
		$(RM) $(OBJS) 
		cd $(LIBFT_DIR) && $(MAKE) clean --silent

fclean:	clean
		$(RM) $(NAME)
		cd $(LIBFT_DIR) && $(MAKE) fclean --silent
		
re:	fclean all

.PHONY:	all clean fclean re