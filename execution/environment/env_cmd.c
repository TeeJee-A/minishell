/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 21:20:45 by ataji             #+#    #+#             */
/*   Updated: 2022/11/16 16:29:10 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_plus_env(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '+' && line[i + 1] != '=')
			return (2);
		if (line[i] == '+' && line[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	find_equal_env(char **line)
{
	int	i;
	int	j;

	i = 1;
	while (line[i])
	{
		j = 0;
		while (line[i][j])
		{
			if (line[i][j] == '=')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	add_val_if_not_exist(t_env *dt, char **line, char **tab)
{
	if (tab[1])
	{
		dt->val = ft_strdup_env(tab[1]);
		dt->sz_val = ft_strlen_env(tab[1]);
		return (1);
	}
	else if (!tab[1])
	{
		if (find_equal_env(line))
		{
			dt->val = ft_strdup_env("");
			dt->sz_val = 1;
		}
		return (1);
	}
	return (2);
}

int	exist_or_not_env(char **tab, char **line)
{
	t_env	*dt;

	dt = g_data.g_envlst;
	while (dt)
	{
		if (ft_strcmp_env(tab[0], dt->var) == 0)
		{
			if (add_val_if_not_exist(dt, line, tab) == 1)
				return (1);
			return (2);
		}
		dt = dt->next;
	}
	return (0);
}

bool	find_equal_environment(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

int	check_plus_exist_env(t_env *dt, char *str1)
{
	t_env	*tmp;
	char	*var;

	tmp = dt;
	var = ft_substr_env(str1, 0, (ft_strlen_env(str1) - 1));
	while (tmp)
	{
		if (!ft_strcmp_env(tmp->var, var))
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
		tmp = tmp->next;
	}
}

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

char	**add_variable_env_one(char **line, t_env *dt, char **tab, int i)
{
	t_env	*tmp;

	tmp = dt;
	if(find_equal_environment(line[i]))
	{
		tab = ft_split_env(line[i], '=');
		if (!tab[1] && !check_plus_exist_env(tmp, tab[0]))
		{
			tmp->val = ft_strdup_env("");
			tmp->sz_val = 1;
		}
	}
	else
	{
		tab = (char **)malloc(2 * sizeof(char *));
		tab[0] = line[i];
		tab[1] = NULL;
	}
	return (tab);
}

void	add_variable_env_two(t_env *dt, char **tab, char **line)
{
	t_env	*tmp;

	tmp = dt;
	tmp->var = ft_strdup_env(tab[0]);
	if (find_equal_env(line))
	{
		tmp->val = ft_strdup_env("");
		tmp->sz_val = 1;
	}
    tmp->sz_var = ft_strlen_env(tab[0]);
    tmp->next = NULL;
}

void	add_variable_env_three(t_env *dt, char **tab)
{
	t_env	*tmp;

	tmp = dt;
	tmp->var = ft_strdup_env(tab[0]);
    tmp->val = ft_strdup_env(tab[1]);
    tmp->sz_var = ft_strlen_env(tab[0]);
    tmp->sz_val = ft_strlen_env(tab[1]);
    tmp->next = NULL;
}

void	add_variable_env(char **line, t_env *dt)
{
	int		i;
	int		k;
	t_env	*tmp;
	char	**tab;
	int		condition;

	i = 0;
	k = 0;
	condition = 0;
	tmp = dt;
	// tab = NULL;
	while (line[++i])
	{
		k = 0;
		tab = add_variable_env_one(line, tmp, tab, i);
		k = exist_or_not_env(tab, line);
		if (line)
		{
			if (ft_check_plus_env(line[i]) == 2)
			{
				printf("Minishell: `%s': Not a valid identifier\n", line[i]);
				return ;
			}
			if (ft_check_plus_env(line[i]) == 1)
			{
				ft_concat_plus_env(dt, line[i]);
				condition = 1;
			}
		}
		while (condition == 0 && k == 0 && tmp && tmp->next)
        	tmp = tmp->next;
		if(condition == 0 && k == 0)
		{
			tmp->next = init_envlst();
    		tmp = tmp->next;
		}
		if (condition == 0 && k == 0 && tab[1])
			add_variable_env_three(tmp, tab);
		if (condition == 0 && k == 0 && !tab[1])
			add_variable_env_two(tmp, tab, line);
	}
}

int	env_cmd(t_execlst *el)
{
	t_env	*tmp;

	tmp = g_data.g_envlst;
	if (el->red && el->red->fd)
	{
		while (tmp)
		{
			if (tmp->sz_val)
			{
				write(el->red->fd, tmp->var, tmp->sz_var);
				write(el->red->fd, "=", 1);
				write(el->red->fd, tmp->val, tmp->sz_val);
			}
			if (tmp->sz_val)
				write(el->red->fd, "\n", 1);
			tmp = tmp->next;
		}
		return (1);
	}
	while (tmp)
	{
		if (tmp->sz_val && tmp->sz_var)
			printf("%s=%s\n", tmp->var, tmp->val);
		tmp = tmp->next;
	}
	return (1);
}
