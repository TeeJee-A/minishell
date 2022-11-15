/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 06:01:07 by ataji             #+#    #+#             */
/*   Updated: 2022/11/15 12:56:53 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*add_path(t_execlst *el)
{
	t_env	*dt;
	char	*path;

	dt = g_data.g_envlst;
	path = NULL;
	while (dt)
	{
		if (check_path(dt->var, "PATH") == 1)
		{
			path = join_path(el);
			break ;
		}
		dt = dt->next;
	}
	return (path);
}

void	execute_command(char *path, t_execlst *el)
{
	if (execve(path, el->cmd, g_data.g_env) == -1)
		print_error(el->cmd[0], "---> Command not found", 127);
}

void	cmd(t_execlst *el, int __pipe[2])
{
	char	*path;

	preexec(el, __pipe);
	if (!el->cmd || !el->cmd[0])
		exit(1);
	path = add_path(el);
	if (!check_if_builtin(el))
	{
		builtin_commands(el);
		exit(0);
	}
	else
	{
		if (el->red && el->red->fd)
			if (ft_red(el) == -1)
				print_error(el->red->file, "No such file or directory", 1);
		execute_command(path, el);
	}
}
