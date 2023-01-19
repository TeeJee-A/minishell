/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaouzi <kfaouzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 01:12:48 by ataji             #+#    #+#             */
/*   Updated: 2022/11/22 13:57:05 by kfaouzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils_char_str.h"
#include "../../includes/minishell.h"

bool	find_equal_export(char *str)
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

int	check_plus_exist_exp(t_env *dt, char *str1)
{
	t_env	*tmp;

	tmp = dt;
	while (tmp)
	{
		if (tmp->var && !ft_strcmp_exp(tmp->var, str1))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	red_export(t_execlst *el, t_env *dt)
{
	t_env	*tmp;

	tmp = dt;
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
}

void	print_export(t_env *dt, int t)
{
	t_env	*tmp;

	tmp = dt;
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
}

int	add_var_exp_env(char **line)
{
	int	check;
	int	i;

	check = 0;
	i = 0;
	while (line[++i])
	{
		if (handle_special_char_exp(line[i]) == 1)
		{
			continue ;
			check = 1;
		}
		add_variable_exp(line[i], &g_data.g_explst);
		add_variable_env(line[i], &g_data.g_envlst);
	}
	return (check);
}
