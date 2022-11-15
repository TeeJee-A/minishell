/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:29:20 by ataji             #+#    #+#             */
/*   Updated: 2022/11/15 10:56:19 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_old_pwd(t_env *dt)
{
	char	*old_pwd;
	char	pwd[1024];
	t_env	*tmp;

	old_pwd = getcwd(pwd, 1024);
	tmp = dt;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var, "OLDPWD"))
		{
			tmp->val = ft_strdup(old_pwd);
			tmp->sz_val = ft_strlen(old_pwd);
		}
		tmp = tmp->next;
	}
}

void	change_pwd(t_env *dt)
{
	char	pwd[1024];
	char	*new_pwd;
	t_env	*tmp;

	new_pwd = getcwd(pwd, 1024);
	tmp = dt;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var, "PWD"))
		{
			tmp->val = ft_strdup(new_pwd);
			tmp->sz_val = ft_strlen(new_pwd);
		}
		tmp = tmp->next;
	}
}

int	cd_cmd(char **line)
{
	change_old_pwd(g_data.g_envlst);
	change_old_pwd(g_data.g_explst);
	if (line[1] == NULL)
	{
		if (!getenv("HOME"))
		{
			printf("Minishell: cd: HOME not set\n");
			return (1);
		}
		chdir(getenv("HOME"));
		change_pwd(g_data.g_envlst);
		change_pwd(g_data.g_explst);
		return (1);
	}
	else if (access(line[1], X_OK) == -1)
		printf("Minishell: cd: %s: Permission denied\n", line[1]);
	else if (chdir(line[1]) == -1)
		printf("Minishell: cd: %s: No such file or directory\n", line[1]);
	change_pwd(g_data.g_envlst);
	change_pwd(g_data.g_explst);
	return (1);
}
