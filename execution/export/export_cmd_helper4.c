/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd_helper4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaouzi <kfaouzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 23:11:44 by ataji             #+#    #+#             */
/*   Updated: 2022/11/22 13:55:07 by kfaouzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils_char_str.h"

void	add_variable_exp(char *line, t_env **dt)
{
	t_env		*tmp;
	t_norm_exp	norm_exp;

	norm_exp.i = 0;
	norm_exp.c = 0;
	if (!*dt)
		*dt = init_explst();
	tmp = *dt;
	norm_exp.tab = add_var_helper2(line, &tmp, norm_exp.tab);
	norm_exp.k = exist_or_not_exp(norm_exp.tab, line);
	if (!add_var_helper3(line))
		return ;
	if (ft_check_plus_exp(line) == 1 && ++norm_exp.c)
		ft_concat_plus_exp(*dt, line);
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

int	export_cmd(char **line, t_execlst *el)
{
	t_env	*tmp;
	int		t;
	int		check;

	t = 0;
	check = 0;
	if (!ft_strcmp_exp(line[1], "="))
	{
		print_error_builtin(line[1], "Not a valid identifier", 1);
		return (1);
	}
	if (my_strlendm(line) > 1)
	{
		t = 1;
		check = add_var_exp_env(line);
	}
	if (check == 1)
		return (1);
	sort_exp(g_data.g_explst);
	tmp = g_data.g_explst;
	if (el->red && el->red->fd && my_strlendm(line) == 1)
		return (red_export(el, tmp), 1);
	print_export(tmp, t);
	return (1);
}
