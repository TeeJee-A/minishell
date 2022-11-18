/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd_helper2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:49:43 by ataji             #+#    #+#             */
/*   Updated: 2022/11/18 10:50:38 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_var_helper(char **line, char **tab, t_env *dt)
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

char	**add_var_helper2(char **line, t_env *dt, char **tab, int i)
{
	t_env	*tmp;

	tmp = dt;
	if (find_equal_export(line[i]))
	{
		tab = ft_split_exp(line[i], '=');
		if (!tab[1] && !check_plus_exist_exp(tmp, tab[0]))
		{
			tmp->val = ft_strdup_exp("");
			tmp->sz_val = 1;
		}
	}
	else
	{
		tab = malloc(2 * sizeof(char *));
		if (!tab)
			ft_exit(1);
		tab[0] = line[i];
		tab[1] = NULL;
	}
	return (tab);
}

void	add_var_helper3(char **line, int i)
{
	if (ft_check_plus_exp(line[i]) == 2)
	{
		print_error_builtin(line[i], \
			"Minishell: `%s': Not a valid identifier", 1);
		return ;
	}
}

void	add_variable_exp(char **line, t_env *dt)
{
	t_env		*tmp;
	t_norm_exp	norm_exp;

	norm_exp.i = 0;
	norm_exp.c = 0;
	tmp = dt;
	while (line[++norm_exp.i])
	{
		norm_exp.tab = add_var_helper2(line, tmp, norm_exp.tab, norm_exp.i);
		norm_exp.k = exist_or_not_exp(norm_exp.tab, line);
		add_var_helper3(line, norm_exp.i);
		if (ft_check_plus_exp(line[norm_exp.i]) == 1 && ++norm_exp.c)
			ft_concat_plus_exp(dt, line[norm_exp.i]);
		while (norm_exp.c == 0 && norm_exp.k == 0 && tmp && tmp->next)
			tmp = tmp->next;
		if (norm_exp.c == 0 && norm_exp.k == 0)
		{
			tmp->next = init_explst();
			tmp = tmp->next;
		}
		if (norm_exp.c == 0 && norm_exp.k == 0 && norm_exp.tab[1])
			add_var_helper1(tmp, norm_exp.tab);
		if (norm_exp.c == 0 && norm_exp.k == 0 && !norm_exp.tab[1])
			add_var_helper(line, norm_exp.tab, tmp);
	}
}
