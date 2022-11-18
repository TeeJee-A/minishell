/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 01:12:48 by ataji             #+#    #+#             */
/*   Updated: 2022/11/17 23:01:29 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	export_cmd(char **line, t_execlst *el)
{
	t_env	*tmp;
	int		t;
	t_env	*dt_exp;
	t_env	*dt_env;

	t = 0;
	dt_exp = g_data.g_explst;
	dt_env = g_data.g_envlst;
	if (my_strlendm(line) > 1)
	{
		t = 1;
		if (handle_special_char_exp(line) == 1)
			return (1);
		add_variable_exp(line, dt_exp);
		add_variable_env(line, dt_env);
	}
	sort_exp(dt_exp);
	tmp = g_data.g_explst;
	if (el->red && el->red->fd && my_strlendm(line) == 1)
	{
		red_export(el, tmp);
		return (1);
	}
	print_export(tmp, t);
	return (1);
}
