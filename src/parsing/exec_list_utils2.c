/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 08:00:51 by kfaouzi           #+#    #+#             */
/*   Updated: 2022/11/21 18:02:16 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils_char_str.h"

t_execlst	*get_execlst(t_tok *tkns)
{
	t_tok		*tmp;
	t_execlst	*exec;
	t_execlst	*hpex;

	exec = NULL;
	hpex = NULL;
	tmp = tkns;
	while (tmp)
	{
		if (tmp->type == WORD || tmp->type == D_QTE || tmp->type == S_QTE)
			hpex = getcmd(hpex, tmp->value);
		else if (tmp->type == RED)
		{
			hpex = getred(hpex, tmp);
			tmp = tmp->next;
		}
		if (!hpex)
			return (NULL);
		if (tmp->type == PIPE || !tmp->next)
			if (add_tknex(&exec, &hpex))
				return (NULL);
		tmp = tmp->next;
	}
	return (exec);
}

int	add_tknex(t_execlst **token, t_execlst **new)
{
	t_execlst	*tmp;

	if (!*new)
		return (1);
	if (token)
	{
		if (*token == NULL)
		{
			*token = *new;
			*new = NULL;
		}
		else
		{
			tmp = *token;
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = *new;
			tmp = NULL;
			*new = NULL;
		}
	}
	return (0);
}

t_execlst	*getred(t_execlst *e, t_tok *tok)
{
	t_red	*t;

	if (!e)
		e = init_execlst();
	if (!e)
		return (NULL);
	e->red = getredlst(e->red, tok);
	t = e->red;
	while (t)
	{
		if (t->type == HEREDC)
		{
			if (ft_strchr(t->file, CHR_D_QT) || ft_strchr(t->file, CHR_S_QT))
				t->dlmtr = 0;
			else
				t->dlmtr = 1;
		}
		t = t->next;
	}
	return (e);
}
