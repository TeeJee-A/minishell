# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kfaouzi <kfaouzi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/19 10:21:20 by kfaouzi           #+#    #+#              #
#    Updated: 2022/11/22 14:57:17 by kfaouzi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
INC = includes/libft.h includes/parsing.h \
	includes/utils_char_str.h includes/execution.h \
	includes/minishell.h

SRCS_LIBFT = src/libft/utils1.c src/libft/utils2.c src/libft/utils3.c \
	src/libft/utils4.c src/libft/utils5.c src/libft/utils6.c src/libft/utils7.c src/libft/ft_split.c

SRC_PRS = src/parsing/tokenizer.c src/parsing/parser1.c src/parsing/parser2.c \
	src/parsing/exec_list_utils1.c src/parsing/exec_list_utils2.c src/parsing/expander1.c \
	src/parsing/expander2.c src/parsing/expander2_utils.c src/parsing/expander3.c

SRC_MINI = execution/first_execution.c execution/execution.c execution/second_execution.c execution/path_execution.c\
	execution/builtin_commands.c execution/echo_cmd.c execution/unset_cmd.c execution/exit_cmd.c execution/pwd_cmd.c\
	execution/cd_cmd.c execution/cmd.c execution/print_error.c execution/garbege.c execution/garbege_helper.c\
	execution/environment/get_env.c execution/environment/ft_split_one.c execution/environment/env_cmd.c execution/environment/env_one.c\
	execution/environment/env_two.c execution/environment/env_three.c execution/environment/env_four.c execution/environment/get_env_utils.c\
	execution/environment/get_env_utils2.c execution/environment/get_env_utils3.c execution/environment/ft_split_env_first.c execution/export/sort_exp.c\
	execution/export/export_cmd.c execution/export/get_exp.c execution/export/get_exp_utils.c execution/export/get_exp_utils2.c execution/export/get_exp_utils3.c\
	execution/export/get_exp_utils4.c execution/export/export_cmd_helper.c execution/export/export_cmd_helper2.c execution/export/export_cmd_helper3.c execution/export/ft_split_exp_first.c\
	execution/export/ft_split_one.c execution/export/export_cmd_helper4.c execution/echo_print.c

SRC_EXEC = src/execution/exec_redirections1.c 


SRC_ENV = src/environment/get_env.c

SRC_SIG = src/signals/signals1.c

SRCS = $(LIBFT) $(SRCS_LIBFT) $(SRC_PRS) $(SRC_EXEC) $(SRC_ENV) $(SRC_SIG) $(SRC_MINI)\
src/main.c

READLINE = $(shell brew --prefix readline)

CFLAGS = -Wall -Werror -Wextra -I$(READLINE)/include

CC = cc
RM = rm -rf
OBJS = $(SRCS:.c=.o)

all:$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -lreadline -L$(READLINE)/lib -o $(NAME) $^

%.o: %.c $(INC)
	echo $(CFLAGS)
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	@$(RM) $(OBJS)

fclean : clean
	@$(RM) $(NAME)

re : fclean all
