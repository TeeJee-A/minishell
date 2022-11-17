/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:16:38 by ataji             #+#    #+#             */
/*   Updated: 2022/11/17 09:51:49 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			printf("\n");
		}
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
	int	cmd;

	fd = dup(STDIN_FILENO);
	cmd = 0;
	g_data.id_cat = 1;
	if (!el->next)
	{
		if (!check_if_builtin(el))
		{
			builtin_commands(el);
			cmd = 1;
		}
	}
	if (!el->next && cmd == 0)
		execve_function(el);
	if (el->next)
		execve_function(el);
	while (1)
		if (wait(&status) == -1)
			break ;
	signal_function(status);
	dup2(fd, STDIN_FILENO);
	close(fd);
}
