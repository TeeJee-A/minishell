/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 21:31:43 by ataji             #+#    #+#             */
/*   Updated: 2022/11/18 10:52:31 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils_char_str.h"
#include "../../includes/minishell.h"

char	*ft_substr_exp(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	if (start < ft_strlen_exp(s))
	{
		if (ft_strlen_exp(s) < len)
			len = ft_strlen_exp(s);
		str = (char *)ft_malloc2((len + 1) * sizeof(char));
		if (!str)
			ft_exit(1);
		while (i < len)
			str[i++] = s[start++];
	}
	else
	{
		str = ft_malloc2(1);
		if (!str)
			ft_exit(1);
	}
	return (str[i] = '\0', str);
}

size_t	ft_strlen_exp(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	ft_swap(char **a, char **b)
{
	char		*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_swapint(int *a, int *b)
{
	int		tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_exp(t_env *dt)
{
	t_env	*tmp;
	t_env	*tmp1;

	tmp = dt;
	tmp1 = dt;
	while (tmp)
	{
		tmp1 = tmp->next;
		while (tmp1)
		{
			if (ft_strcmp_exp(tmp->var, tmp1->var) > 0)
			{
				ft_swap(&tmp->var, &tmp1->var);
				ft_swap(&tmp->val, &tmp1->val);
				ft_swapint(&tmp->sz_val, &tmp1->sz_val);
				ft_swapint(&tmp->sz_var, &tmp1->sz_var);
			}
			tmp1 = tmp1->next;
		}
		tmp = tmp->next;
	}
}
