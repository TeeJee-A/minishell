/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaouzi <kfaouzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 19:52:23 by ataji             #+#    #+#             */
/*   Updated: 2022/11/22 12:44:37 by kfaouzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils_char_str.h"
#include "../includes/minishell.h"

int	pwd_cmd(t_execlst *el)
{
	int		j;
	char	cwd[256];

	if (getenv_from_my_env("PWD"))
		g_data.fix_pwd = getenv_from_my_env("PWD");
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		printf("%s\n", g_data.fix_pwd);
		return (1);
	}
	if (el->red && el->red->fd)
	{
		j = 0;
		while (el->red->next)
			el->red = el->red->next;
		while (cwd[j])
		{
			write (el->red->fd, &cwd[j], 1);
			j++;
		}
		write (el->red->fd, "\n", 1);
	}
	else
		printf("%s\n", cwd);
	return (1);
}

char	*creat_execution_file(char *path)
{
	int		i;
	char	*new_path;

	i = 2;
	new_path = my_substr(path, i, my_strlen(path));
	return (new_path);
}
