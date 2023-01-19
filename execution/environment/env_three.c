/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_three.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:20:32 by ataji             #+#    #+#             */
/*   Updated: 2022/11/22 00:15:21 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils_char_str.h"
#include "../../includes/minishell.h"

int	ft_replace_value_env(t_env *dt, char *var, char *val)
{
	t_env	*tmp;

	tmp = dt;
	while (tmp)
	{
		if (!ft_strcmp_env(tmp->var, var))
		{
			if (!tmp->val)
			{
				tmp->val = ft_strdup_env(val);
				tmp->sz_val = ft_strlen_env(val);
			}
			else
				tmp->val = ft_strjoin_env(tmp->val, val);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_replace_value_variable_env(t_env *dt, char *var, char *val)
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
	tmp->var = ft_strdup_env(var);
	tmp->val = ft_strdup_env(val);
	tmp->sz_val = ft_strlen_env(tmp->val);
	tmp->sz_var = ft_strlen_env(tmp->var);
}

void	ft_concat_plus_env(t_env *dt, char *line)
{
	char	**tab;
	char	*var;
	char	*val;
	t_env	*tmp;
	int		condition;

	tmp = dt;
	condition = 0;
	tab = ft_split_env(line, '=');
	var = ft_substr_env(tab[0], 0, (ft_strlen_env(tab[0]) - 1));
	if (!tab[1])
	{
		add_before_with_plus_env(var, tmp);
		return ;
	}
	val = ft_strdup_env(tab[1]);
	if (ft_replace_value_env(tmp, var, val) == 1)
		return ;
	ft_replace_value_variable_env(tmp, var, val);
}

void	fonction_helper(t_env **dt)
{
	t_env	*tmp;

	tmp = *dt;
	tmp->next = init_explst();
	tmp = tmp->next;
	tmp->val = ft_strdup_env("");
	tmp->sz_val = 1;
}

char	**add_variable_env_one(char *line, t_env **dt, char **tab)
{
	t_env	*tmp;

	tmp = *dt;
	tab = ft_split_env(line, '=');
	if (ft_check_plus_env(line) == 0)
	{
		if (find_equal_environment(line))
		{
			while (tmp->next)
				tmp = tmp->next;
			if (!tab[1] && !check_plus_exist_env(tmp, tab[0]))
				fonction_helper(&tmp);
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
