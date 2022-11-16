/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:29:20 by ataji             #+#    #+#             */
/*   Updated: 2022/11/16 09:27:43 by ataji            ###   ########.fr       */
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
		if (!my_strcmp(tmp->var, "OLDPWD"))
		{
			if (tmp->sz_val)
			{
				tmp->val = my_strdup(old_pwd);
				tmp->sz_val = my_strlen(old_pwd);
			}
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
		if (!my_strcmp(tmp->var, "PWD"))
		{
			tmp->val = my_strdup(new_pwd);
			tmp->sz_val = my_strlen(new_pwd);
		}
		tmp = tmp->next;
	}
}

int	mini_cd_cmd(void)
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

int	cd_cmd(char **line)
{
	char	cwd[1024];

	change_old_pwd(g_data.g_envlst);
	change_old_pwd(g_data.g_explst);
	if (!getcwd(cwd, 1024))
		if (chdir(line[1]) == -1)
			return (1);
	if (line[1] == NULL)
	{
		mini_cd_cmd();
		return (1);
	}
	else if (access(line[1], F_OK) == -1)
		printf("Minishell: cd: %s: No such file or directory\n", line[1]);
	else if (access(line[1], X_OK) == -1)
		printf("Minishell: cd: %s: Permission denied\n", line[1]);
	else
		if (chdir(line[1]) == -1)
			return (1);
	change_pwd(g_data.g_envlst);
	change_pwd(g_data.g_explst);
	return (1);
}
