/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:38:11 by ataji             #+#    #+#             */
/*   Updated: 2022/11/21 08:57:29 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils_char_str.h"
#include "../../includes/minishell.h"

t_env	*init_explst(void)
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

void	get_exp_empty(t_env *dt)
{
	char	pwd[256];

	getcwd(pwd, sizeof(pwd));
	dt->var = ft_strdup_exp("OLDPWD");
	dt->sz_var = ft_strlen_exp("OLDPWD");
	dt->next = init_explst();
	dt = dt->next;
	dt->var = ft_strdup_exp("PWD");
	dt->val = ft_strdup_exp(pwd);
	dt->sz_var = ft_strlen_exp("PWD");
	dt->sz_val = ft_strlen_exp(pwd);
	dt->next = init_explst();
	dt = dt->next;
	dt->var = ft_strdup_exp("SHLVL");
	dt->val = ft_strdup_exp("1");
	dt->sz_var = ft_strlen_exp("SHLVL");
	dt->sz_val = 1;
}

void	get_exp(t_env *dt)
{
	int		i;
	char	**tab;

	i = 0;
	while (g_data.g_exp[++i])
	{
		tab = ft_split_exp_first(g_data.g_exp[i], '=');
		dt->var = ft_strdup_exp(tab[0]);
		dt->val = ft_strdup_exp(tab[1]);
		dt->sz_var = ft_strlen_exp(tab[0]);
		dt->sz_val = ft_strlen_exp(tab[1]);
		g_data.lenexplst++;
		if (g_data.g_exp[i + 1])
		{
			dt->next = init_explst();
			dt = dt->next;
		}
	}
}
