/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_two.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaouzi <kfaouzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:19:10 by ataji             #+#    #+#             */
/*   Updated: 2022/11/22 14:20:47 by kfaouzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils_char_str.h"
#include "../../includes/minishell.h"

int	check_plus_exist_env(t_env *dt, char *str1)
{
	t_env	*tmp;
	char	*var;

	tmp = dt;
	var = ft_substr_env(str1, 0, (ft_strlen_env(str1) - 1));
	while (tmp)
	{
		if (tmp->var && !ft_strcmp_env(tmp->var, var))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	plus_cmp_env(char *var)
{
	t_env	*dt;

	dt = g_data.g_explst;
	while (dt)
	{
		if (!ft_strcmp_env(var, dt->var))
			return (1);
		dt = dt->next;
	}
	return (0);
}

void	add_before_with_plus_two(t_env *dt, char *var)
{
	t_env	*tmp;

	tmp = dt;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
	{
		tmp->next = init_envlst();
		tmp = tmp->next;
	}
	if (!tmp->val)
	{
		tmp->var = var;
		tmp->val = ft_strdup_env("");
		tmp->sz_val = 1;
		tmp->sz_var = ft_strlen_env(var);
		return ;
	}
}

void	add_before_with_plus_env(char *var, t_env *tmp)
{
	while (tmp)
	{
		if (plus_cmp_env(var))
		{
			if (!tmp->val)
			{
				tmp->val = ft_strdup_env("");
				tmp->sz_val = 1;
				return ;
			}
		}
		else
		{
			add_before_with_plus_two(tmp, var);
			if (!tmp->val)
				return ;
		}
		tmp = tmp->next;
	}
}
