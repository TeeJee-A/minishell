/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 01:12:48 by ataji             #+#    #+#             */
/*   Updated: 2022/11/10 18:28:52 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exist_or_not_exp(char **tab, char **line)
{
	t_env	*dt;

	dt = g_data.g_explst;
	while (dt)
	{
		if (ft_strcmp_exp(tab[0], dt->var) == 0)
		{
			if(tab[1])
			{
        		dt->val = ft_strdup_exp(tab[1]);
        		dt->sz_val = ft_strlen_exp(tab[1]);
				return (1);
			}
			else if (!tab[1])
			{
				if (find_equal_exp(line))
				{
					dt->val = ft_strdup_exp("");
					dt->sz_val = 1;
				}
				return (1);
			}
			return (2);
		} 
		dt = dt->next;
	}
	return (0);
}

int	find_equal_exp(char **line)
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

int	check_if_in_export(char *variable)
{
	t_env	*dt;
	
	dt = g_data.g_explst;
	while (dt)
	{
		if (!ft_strcmp(variable, dt->var))
			return (0);
		dt = dt->next;
	}
	return (1);
}

int	check_if_dollar(char *dollar)
{
	int		i;
	char	*next_dollar;
	int		size_dollar;
	t_env	*dt;

	i = 0;
	dt = g_data.g_explst;
	next_dollar = ft_substr_exp(dollar, 1, ft_strlen_exp(dollar));
	size_dollar = ft_strlen_exp(next_dollar);
	if (size_dollar)
	{
		if (!check_if_in_export(next_dollar))
		{
			printf("Minishell: `%s': Not a valid identifier\n", next_dollar);
			return (1);
		}
		else
		{
			if (dt->sz_val)
				printf("declare -x %s=\"%s\"\n", dt->var, dt->val);
			else
				printf("declare -x %s\n", dt->var);
			return (1);
		}
	}
	return (0);
}

int	special_char(char *line, char **tab)
{
	int	i;
	int	j;
	char	*special;

	special = "$+,~^=}]/:\'\"%.0123456789";
	i = 1;
	if (line)
	{
		while (tab[i])
		{
			j = 0;
			while (special[j])
			{
				if (line[0] == special[j])
				{
					printf("Minishell: `%s': Not a valid identifier\n", tab[i]);
					return (1);
				}
				j++;
			}
			i++;
		}
	}
	return (0);
}

int	find_it_exp(char **tab)
{
	int		i;
	int		j;
	int		count;
	char	*special;
	char	*line;

	i = 0;
	count = 0;
	special = "-$+,~^=}]/:\'\"%.0123456789";
	while (tab[i])
	{
		line = ft_strdup_exp(tab[i]);
		j = 0;
		while (special[j])
		{
			if (line[0] == special[j])
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int	handle_special_char_exp(char **line)
{
	int	i;
	int	j;
	int	count;
	int	check;

	i = 0;
	j = 1;
	check = 0;
	count = find_it_exp(line);
	while (i < count)
	{
		printf("Minishell: `%s': Not a valid identifier\n", line[j]);
		i++;
		j++;
		check = 1;
	}
	if (check == 1)
		return (1);
	return (0);
}

bool find_equal_export(char *str)
{
	int i = 0;
	while(str[i])
	{
		if(str[i] == '=')
			return(true);
		i++;
	}
	return(false);
}

int	check_plus_exist_exp(t_env *dt, char *str1)
{
	t_env	*tmp;
	char	*var;

	tmp = dt;
	var = ft_substr_exp(str1, 0, (ft_strlen_exp(str1) - 1));
	while (tmp)
	{
		if (!ft_strcmp_exp(tmp->var, var))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	add_variable_exp(char **line, t_env *dt)
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
	while (line[++i])
	{
		k = 0;
		if (handle_special_char_exp(line) == 1)
			return ;
		if(find_equal_export(line[i]))
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
			tab = (char **)malloc(2 * sizeof(char *));
			tab[0] = line[i];
			tab[1] = NULL;
		}
		k = exist_or_not_exp(tab, line);
		if (line)
		{
			if (ft_check_plus_exp(line[i]) == 2)
			{
				printf("Minishell: `%s': Not a valid identifier\n", line[i]);
				return ;
			}
			if (ft_check_plus_exp(line[i]) == 1)
			{
				ft_concat_plus_exp(dt, line[i]);
				condition = 1;
			}
		}
		while (condition == 0 && k == 0 && tmp && tmp->next)
        	tmp = tmp->next;
		if(condition == 0 && k == 0)
		{
			tmp->next = init_explst();
    		tmp = tmp->next;
		}
		if (condition == 0 && k == 0 && tab[1])
		{
			tmp->var = ft_strdup_exp(tab[0]);
            tmp->val = ft_strdup_exp(tab[1]);
            tmp->sz_var = ft_strlen_exp(tab[0]);
            tmp->sz_val = ft_strlen_exp(tab[1]);
            tmp->next = NULL;
		}
		if (condition == 0 && k == 0 && !tab[1])
		{
			tmp->var = ft_strdup_exp(tab[0]);
			if (find_equal_exp(line))
			{
				tmp->val = ft_strdup_exp("");
				tmp->sz_val = 1;
			}
            tmp->sz_var = ft_strlen_exp(tab[0]);
            tmp->next = NULL;
		}
	}
}

int export_cmd(char **line, t_execlst *el)
{
	t_env   *tmp;
	int		t;
	t_env	*dt_exp;
	t_env	*dt_env;

	t = 0;
	dt_exp = g_data.g_explst;
	dt_env = g_data.g_envlst;
	if (ft_strlendm(line) > 1)
	{
		t = 1;
		add_variable_exp(line, dt_exp);
		add_variable_env(line, dt_env);
	}
	sort_exp(dt_exp);
	tmp = g_data.g_explst;
	if (el->red && el->red->fd && ft_strlendm(line) == 1)
	{
		while (tmp)
		{
			write(el->red->fd, "declare -x ", 11);
			write(el->red->fd, tmp->var, tmp->sz_var);
			if (tmp->sz_val)
			{
				write(el->red->fd, "=\"", 2);
				write(el->red->fd, tmp->val, tmp->sz_val);
				write(el->red->fd, "\"", 1);
			}
			write(el->red->fd, "\n", 1);
			tmp = tmp->next;
		}
		return (1);
	}
	while (tmp && !(t))
	{
		if (tmp->sz_var)
		{
			if (tmp->sz_val)
				printf("declare -x %s=\"%s\"\n", tmp->var, tmp->val);
			else
				printf("declare -x %s\n", tmp->var);
		}
		tmp = tmp->next;
	}
	return (1);
}
