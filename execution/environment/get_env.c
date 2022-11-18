/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 06:02:36 by ataji             #+#    #+#             */
/*   Updated: 2022/11/18 10:50:17 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils_char_str.h"
#include "../../includes/minishell.h"

t_env	*init_envlst(void)
{
	t_env	*e;

	e = ft_malloc2(sizeof(t_env));
	if (!e)
		ft_exit(1);
	e->var = NULL;
	e->val = NULL;
	e->sz_var = 0;
	e->sz_val = 0;
	e->next = NULL;
	return (e);
}

void	get_env_empty(t_env *dt)
{
	char	pwd[1024];

	getcwd(pwd, sizeof(pwd));
	dt->var = ft_strdup_env("PWD");
	dt->val = ft_strdup_env(pwd);
	dt->sz_var = ft_strlen_env("PWD");
	dt->sz_val = ft_strlen_env(pwd);
	dt->next = init_envlst();
	dt = dt->next;
	dt->var = ft_strdup_env("SHLVL");
	dt->val = ft_strdup_env("1");
	dt->sz_var = ft_strlen_env("SHLVL");
	dt->sz_val = 1;
	dt->next = init_envlst();
	dt = dt->next;
	dt->var = ft_strdup_env("_");
	dt->val = ft_strdup_env("/usr/bin/env");
	dt->sz_var = 1;
	dt->sz_val = ft_strlen_env("/usr/bin/env");
}

void	get_env(t_env *dt)
{
	int		i;
	char	**tab;

	i = 0;
	while (g_data.g_env[++i])
	{
		tab = ft_split_env_first(g_data.g_env[i], '=');
		dt->var = ft_strdup_env(tab[0]);
		dt->val = ft_strdup_env(tab[1]);
		dt->sz_var = ft_strlen_env(tab[0]);
		dt->sz_val = ft_strlen_env(tab[1]);
		g_data.lenenvlst++;
		if (g_data.g_env[i + 1])
		{
			dt->next = init_envlst();
			dt = dt->next;
		}
	}
}
