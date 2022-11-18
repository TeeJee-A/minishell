/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:16:38 by ataji             #+#    #+#             */
/*   Updated: 2022/11/18 10:43:30 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils_char_str.h"
#include "../includes/minishell.h"

int	check_redir(t_execlst *el)
{
	int	i;

	i = 0;
	while (el->cmd[i])
	{
		if (el->red)
			return (0);
		i++;
	}
	return (1);
}

void	signal_function(int status)
{
	g_data.exit_status = 0;
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			printf("\n");
		if (WTERMSIG(status) == SIGQUIT)
			printf("Quit: 3\n");
		g_data.exit_status = 128 + WTERMSIG(status);
	}
	if (WIFEXITED(status))
		g_data.exit_status = WEXITSTATUS(status);
}

void	mini_token_and_exec(t_execlst *el)
{
	int	fd;
	int	status;

	fd = dup(STDIN_FILENO);
	g_data.id_cat = 1;
	if (!el->next)
	{
		if (!check_if_builtin(el))
		{
			if (builtin_commands(el) == -1)
				return ;
		}
		else
			execve_function(el);
	}
	if (el->next)
		execve_function(el);
	while (1)
		if (wait(&status) == -1)
			break ;
	signal_function(status);
	dup2(fd, STDIN_FILENO);
	close(fd);
}
