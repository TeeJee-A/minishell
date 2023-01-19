/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd_helper2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaouzi <kfaouzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:49:43 by ataji             #+#    #+#             */
/*   Updated: 2022/11/22 12:50:59 by kfaouzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils_char_str.h"
#include "../../includes/minishell.h"

void	add_var_helper(char *line, char **tab, t_env *dt)
{
	t_env	*tmp;

	tmp = dt;
	tmp->var = ft_strdup_exp(tab[0]);
	if (find_equal_exp(line))
	{
		tmp->val = ft_strdup_exp("");
		tmp->sz_val = 1;
	}
	tmp->sz_var = ft_strlen_exp(tab[0]);
	tmp->next = NULL;
}

void	add_var_helper1(t_env *dt, char **tab)
{
	t_env	*tmp;

	tmp = dt;
	tmp->var = ft_strdup_exp(tab[0]);
	tmp->val = ft_strdup_exp(tab[1]);
	tmp->sz_var = ft_strlen_exp(tab[0]);
	tmp->sz_val = ft_strlen_exp(tab[1]);
	tmp->next = NULL;
}

void	with_equal_without_val(t_env **dt, char **tab)
{
	t_env	*tmp;

	tmp = *dt;
	while (tmp->next)
		tmp = tmp->next;
	if (!tab[1] && !check_plus_exist_exp(tmp, tab[0]))
	{
		tmp->next = init_explst();
		tmp = tmp->next;
		if (ft_strcmp_exp(tmp->var, tab[0]))
		{
			tmp->var = ft_strdup_exp(tab[0]);
			tmp->sz_var = ft_strlen_exp(tab[0]);
			tmp->val = ft_strdup_exp("");
			tmp->sz_val = 1;
		}
		else
		{
			tmp->val = ft_strdup_exp("");
			tmp->sz_val = 1;
		}
	}
}

int	check_exist_var(char *var, t_env *dt)
{
	t_env	*tmp;

	tmp = dt;
	while (tmp)
	{
		if (!ft_strcmp_exp(tmp->var, var))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	**add_var_helper2(char *line, t_env **dt, char **tab)
{
	t_env	*tmp;

	tmp = *dt;
	tab = ft_split_exp(line, '=');
	if (ft_check_plus_exp(line) == 0)
	{
		if (find_equal_export(line))
		{
			if (check_exist_var(tab[0], *dt) == 0)
				with_equal_without_val(&tmp, tab);
		}
		else
		{
			tab = ft_malloc2(2 * sizeof(char *));
			if (!tab)
				ft_exit(1);
			tab[0] = line;
			tab[1] = NULL;
		}
	}
	return (tab);
}
