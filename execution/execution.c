/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:16:38 by ataji             #+#    #+#             */
/*   Updated: 2022/11/16 15:03:43 by ataji            ###   ########.fr       */
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

void	mini_token_and_exec(t_execlst *el)
{
	int	fd;
	int	status;
	int	cmd;

	fd = dup(STDIN_FILENO);
	cmd = 0;
	
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
	else if (el->next)
		execve_function(el);
	while (1)
		if (wait(&status) == -1)
			break ;
	if (WIFEXITED(status))
		g_data.exit_status = WEXITSTATUS(status);
	dup2(fd, STDIN_FILENO);
	close(fd);
}
