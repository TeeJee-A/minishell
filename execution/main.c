/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:54:02 by ataji             #+#    #+#             */
/*   Updated: 2022/11/17 10:20:28 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing.h"

char	*change_app_to_low(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] >= 65 && cmd[i] <= 90)
			cmd[i] += 32;
		i++;
	}
	return (cmd);
}

int	check_if_builtin(t_execlst *el)
{
	char	*cmd;
	char	**tab;
	int		i;

	i = 0;
	if (!el->cmd || !*el->cmd)
		return (0);
	if (!el)
		return (0);
	el->cmd[0] = change_app_to_low(*el->cmd);
	cmd = "echo exit pwd cd env export unset";
	tab = my_split(cmd, ' ');
	while (tab[i])
	{
		if (my_strcmp(tab[i++], el->cmd[0]) == 0)
			return (0);
	}
	return (1);
}

int	check_access_file(t_execlst *el, int check_next)
{
	while (el)
	{
		if (el->red && el->red->file)
		{
			if (access(el->red->file, F_OK) == -1)
			{
				if (check_next == 1)
				{
					print_error_builtin(el->red->file, \
						"No such file or directory", 1);
					return (0);
				}
				else
					print_error(el->red->file, "No such file or directory", 1);
			}
		}
		el = el->next;
	}
	return (1);
}

void	dup_function(int fd_out, int fd_in)
{
	if (fd_out != -1)
	{
		dup2(fd_out, 1);
		close(fd_out);
	}
	if (fd_in != -1)
	{
		dup2(fd_in, 0);
		close(fd_in);
	}
}

int	ft_red(t_execlst *el, int *dup1, int *dup0)
{
	int fd_out;
	int fd_in;

	*dup1 = dup(1);
	*dup0 = dup(0);
	fd_out = -1;
	fd_in = -1;
	while(el->red)
	{
		if (el->red->fd < 0)
			return (-1);
		if (el->red->type == 6 || el->red->type == 8)
			fd_out = el->red->fd;
		if (el->red->type == 5 || el->red->type == 7)
			fd_in = el->red->fd;
		el->red = el->red->next;
	}
	dup_function(fd_out, fd_in);
	return (0);
}

int	check_path(char *var, char *p)
{
	if (my_strcmp(var, p) != 0)
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
	tab = my_split(old_path, ':');
	i = 0;
	while (line[i])
	{
		j = 0;
		while (tab[j])
		{
			command = my_strjoin("/", line[i]);
			path = my_strjoin(tab[j], command);
			if (access(path, X_OK) == 0)
				return (path);
			j++;
		}
		i++;
	}
	return (NULL);
}

char	*creat_execution_file(char *path)
{
	int		i;
	char	*new_path;

	i = 2;
	new_path = my_substr(path, i, my_strlen(path));
	return (new_path);
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
	else if (element->cmd[i][j] == '.' && element->cmd[i][j + 1] == '/')
		path = creat_execution_file(element->cmd[i]);
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
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			cmd(el, __pipe);
		}
		postexec(el, __pipe);
		el = el->next;
	}
}
