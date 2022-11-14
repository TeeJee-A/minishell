/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:54:02 by ataji             #+#    #+#             */
/*   Updated: 2022/11/14 16:12:15 by ataji            ###   ########.fr       */
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

int	check_access_file(t_execlst *el)
{
	while (el)
	{
		if (el->red && el->red->file)
		{
			if (access(el->red->file, F_OK) == -1)
			{
				printf("Minishell: %s: No such file or directory\n", el->red->file);
				g_data.exit_status = 1;
				return (0);
			}
		}
		el = el->next;
	}
	return (1);
}

int    builtin_commands(t_execlst *el)
{
	int		ck;

	ck = 0;
	if (check_access_file(el) == 0)
		return (2);
	if (el && el->cmd && el->cmd[0])
	{
		if (!(ft_strcmp(el->cmd[0], "echo")))
		{
			if (el->cmd[1] == NULL && !el->red)
			{
				write (1, "\n", 1);
				ck = 1;
			}
			else
				ck = echo_cmd(el);
		}
		else if (!(ft_strcmp(el->cmd[0], "exit")))
			exit_cmd();
		else if (!(ft_strcmp(el->cmd[0], "pwd")))
			ck = pwd_cmd(el);
		else if (!(ft_strcmp(el->cmd[0], "cd")))
			ck = cd_cmd(el->cmd);
		else if (!(ft_strcmp(el->cmd[0], "env")))
			ck = env_cmd(el);
		else if (!(ft_strcmp(el->cmd[0], "export")))
			ck = export_cmd(el->cmd, el);
		else if (!(ft_strcmp(el->cmd[0], "unset")))
		{
			ck = unset_env(el->cmd);
			ck = unset_exp(el->cmd);
		}
	}
	return (ck);
}

void	print_error(char *s1, char *s2, int error)
{
	printf("Minishell: %s: %s\n", s1, s2);
	exit(error);
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
