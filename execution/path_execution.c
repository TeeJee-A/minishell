/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:52:00 by ataji             #+#    #+#             */
/*   Updated: 2022/11/22 00:06:26 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils_char_str.h"
#include "../includes/minishell.h"

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

char	*getenv_from_my_env(char *key)
{
	t_env	*dt;

	dt = g_data.g_envlst;
	while (dt)
	{
		if (!ft_strcmp_env(dt->var, key))
			return (dt->val);
		dt = dt->next;
	}
	return (NULL);
}

char	*creat_path(char **line, char *path)
{
	char	*command;
	char	*old_path;
	char	**tab;
	int		i;
	int		j;

	old_path = getenv_from_my_env("PATH");
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
