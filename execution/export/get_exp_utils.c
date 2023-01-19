/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exp_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 21:05:25 by ataji             #+#    #+#             */
/*   Updated: 2022/11/21 23:00:43 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils_char_str.h"
#include "../../includes/minishell.h"

void	add_before_with_plus_one(char *var, t_env *dt)
{
	t_env	*tmp;

	tmp = dt;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
	{
		tmp->next = init_explst();
		tmp = tmp->next;
	}
	if (!tmp->val)
	{
		tmp->var = var;
		tmp->val = ft_strdup_exp("");
		tmp->sz_val = 1;
		tmp->sz_var = ft_strlen_exp(var);
		return ;
	}
}

void	add_before_with_plus_exp(char *var, t_env *tmp)
{
	while (tmp)
	{
		if (plus_cmp_exp(var))
		{
			if (!tmp->val)
			{
				tmp->val = ft_strdup_exp("");
				tmp->sz_val = 1;
				return ;
			}
		}
		else
		{
			add_before_with_plus_one(var, tmp);
			if (!tmp->val)
				return ;
		}
		tmp = tmp->next;
	}
}

void	ft_concat_plus_exp(t_env *dt, char *line)
{
	char	**tab;
	char	*var;
	char	*val;
	t_env	*tmp;
	int		condition;

	tmp = dt;
	condition = 0;
	tab = ft_split_exp(line, '=');
	var = ft_substr_exp(tab[0], 0, (ft_strlen_exp(tab[0]) - 1));
	if (!tab[1])
	{
		add_before_with_plus_exp(var, tmp);
		return ;
	}
	val = ft_strdup_exp(tab[1]);
	if (ft_replace_value_exp(tmp, var, val) == 1)
		return ;
	ft_replace_value_variable_exp(tmp, var, val);
}

char	*ft_strdup_exp(const char *s1)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)ft_malloc2(ft_strlen_exp(s1) + 1 * sizeof(char));
	if (!str)
		ft_exit(1);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin_exp(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	sl1;
	size_t	sl2;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	sl1 = ft_strlen_exp (s1);
	sl2 = ft_strlen_exp (s2);
	str = (char *)ft_malloc2((sl1 + sl2 + 1) * sizeof(char));
	if (!str)
		ft_exit(1);
	while (i < sl1)
	{
		str[i] = s1[i];
		i++;
	}
	while (j < sl2)
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}
