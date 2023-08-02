NAME		= minishell
CC			= gcc
CFLAGS		=  -Wall -Wextra -Werror -g
RM			= rm -f
SRCS	=	main.c utils.c env/set_env.c cmd/close.c cmd/cmd.c cmd/run_cmd.c \
			free/free.c env/set_path.c error/error.c lexer/array.c lexer/cleaner.c lexer/dollar.c \
			lexer/lexer.c lexer/process.c redirect/input.c redirect/output.c redirect/redirect.c tokenize/parse_string.c \
			redirect/heredoc.c tokenize/tokenize.c utils/is_heredoc.c utils/is_operator.c utils/is_parent.c utils/is_whitespace.c utils/ft_strcmp.c\
			builtin/builtin.c builtin/echo.c builtin/cd_pwd.c builtin/export.c builtin/export_utils.c builtin/input_output.c builtin/utils.c pipes/pipes.c
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