NAME = minishell
LIBFT = execution/libft/libft.a
INC = includes/libft.h includes/parsing.h \
	includes/utils_char_str.h includes/execution.h \
	includes/minishell.h

SRCS_LIBFT = src/libft/utils1.c src/libft/utils2.c src/libft/utils3.c \
	src/libft/utils4.c src/libft/utils5.c src/libft/utils6.c src/libft/ft_split.c

SRC_PRS = src/parsing/tokenizer.c src/parsing/parser1.c src/parsing/parser2.c \
	src/parsing/exec_list_utils1.c src/parsing/exec_list_utils2.c src/parsing/expander1.c \
	src/parsing/expander2.c src/parsing/expander2_utils.c src/parsing/expander3.c

SRC_MINI = execution/main.c\
	execution/echo_cmd.c\
	execution/exit_cmd.c\
	execution/pwd_cmd.c\
	execution/cd_cmd.c\
	execution/cmd.c\
	execution/environment/get_env.c\
	execution/environment/env_cmd.c\
	execution/environment/get_env_utils.c\
	execution/environment/get_env_utils2.c\
	execution/environment/ft_split_env_first.c\
	execution/export/sort_exp.c\
	execution/export/export_cmd.c\
	execution/export/get_exp.c\
	execution/export/get_exp_utils.c\
	execution/export/get_exp_utils2.c\
	execution/unset_cmd.c\
	execution/export/ft_split_exp_first.c\
	execution/path_exec.c\
	execution/builtin_commands.c\
	execution/print_error.c\
	execution/execution.c

SRC_EXEC = src/execution/exec_redirections1.c 


SRC_ENV = src/environment/get_env.c

SRC_SIG = src/signals/signals1.c

SRCS = $(SRCS_LIBFT) $(SRC_PRS) $(SRC_EXEC) $(SRC_ENV) $(SRC_SIG) $(SRC_MINI)\
src/main.c

CFLAGS = -Wall -Werror -Wextra  -g -I/goinfre/ataji/.brew/opt/readline/include
CC = cc
RM = rm
OBJS = $(SRCS:.c=.o)

all:$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LIBFT) -lreadline -L/goinfre/ataji/.brew/opt/readline/lib -o $(NAME) $^

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	@$(RM) $(OBJS)

fclean : clean
	@$(RM) $(NAME)

re : fclean all


# -L/goinfre/kfaouzi/homebrew/opt/readline/lib