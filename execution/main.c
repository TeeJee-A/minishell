/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:54:02 by ataji             #+#    #+#             */
/*   Updated: 2022/11/15 12:49:13 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing.h"

int	check_if_builtin(t_execlst *el)
{
	char	*cmd;
	char	**tab;
	int		i;

	i = 0;
	cmd = "echo exit pwd cd env export unset";
	tab = ft_split(cmd, ' ');
	while (tab[i])
	{
		if (ft_strcmp(tab[i++], el->cmd[0]) == 0)
			return (0);
	}
	return (1);
}

int	check_access_file(t_execlst *el, int check_next)
{
	while (el)
	{
		if (el->red && el->red->file)
			if (access(el->red->file, F_OK) == -1)
			{
				if (check_next == 1)
				{
					print_error_builtin(el->red->file, "No such file or directory", 1);
					return (0);
				}
				else
					print_error(el->red->file, "No such file or directory", 1);
			}
		el = el->next;
	}
	return (1);
}

int	ft_red(t_execlst *el)
{
	if (el && el->red && el->red->fd < 0)
		return (-1);
	if (el && el->red && (el->red->type == REDOUT || el->red->type == APPND))
	{
		
		dup2(el->red->fd, 1);
		close(el->red->fd);
		return (1);
	}
	if (el && el->red && (el->red->type == REDIN || el->red->type == HEREDC))
	{
		dup2(el->red->fd, 0);
		close(el->red->fd);
		return (1);
	}
	return (0);
}

int	check_path(char *var, char *p)
{
	if (ft_strcmp(var, p) != 0)
		return (0);
	return (1);
}

char	*relative_path(char *line)
{
	if (access(line, F_OK) == -1)
		print_error(line, "No such file or directory", 127);
	else if (access(line, X_OK) == -1)
		print_error(line, "Permission denied", 1);
	return (line);
}

char	*creat_path(char **line, char *path)
{
	char	*command;
	char	*old_path;
	char	**tab;
	int		i;
	int		j;

	old_path = getenv("PATH");
	tab = ft_split(old_path, ':');
	i = 0;
	while (line[i])
	{
		j = 0;
		while (tab[j])
		{
			command = ft_strjoin("/", line[i]);
			path = ft_strjoin(tab[j], command);
			if (access(path, X_OK) == 0)
				return (path);
			j++;
		}
		i++;
	}
	return (NULL);
}

char	*join_path(t_execlst *el)
{
	char		*path;
	t_execlst	*element;
	int			i;
	int			j;

	path = NULL;
	element = el;
	i = 0;
	j = 0;
	if (element->cmd[i][j] == '/' && !element->cmd[i][j + 1])
		print_error(element->cmd[i], "is a directory", 126);
	else if (element->cmd[i][j] == '/' && element->cmd[i][j + 1])
		path = relative_path(element->cmd[i]);
	else if (element->cmd[i])
		path = creat_path(element->cmd, path);
	return (path);
}

void	preexec(t_execlst *el, int pipe[2])
{
	if (el->next)
	{
		dup2(pipe[W], STDOUT_FILENO);
		close(pipe[R]);
		close(pipe[W]);
	}
}

void	postexec(t_execlst *el, int pipe[2])
{
	if (el->next)
	{
		dup2(pipe[R], STDIN_FILENO);
		close(pipe[R]);
		close(pipe[W]);
	}
	else
		close(0);
}

void	ft_pipe(t_execlst *el, int __pipe[2])
{
	if (el->next)
	{
		if (pipe(__pipe) == -1)
		{
			perror("pipe");
			exit(1);
		}
	}
}

void	execve_function(t_execlst *el)
{
	int	pid;
	int	__pipe[2];

	while (el)
	{
		ft_pipe(el, __pipe);
		pid = fork();
		if (pid < 0)
			return (perror("fork"));
		if (pid == 0)
			cmd(el, __pipe);
		postexec(el, __pipe);
		el = el->next;
	}
}
