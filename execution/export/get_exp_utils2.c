/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exp_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 21:13:19 by ataji             #+#    #+#             */
/*   Updated: 2022/11/18 10:51:41 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils_char_str.h"
#include "../../includes/minishell.h"

char	**ft_freeing_exp(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

char	*get_var_name_exp(const char *s, int index)
{
	char	*var_name;
	int		i;

	var_name = ft_malloc2(index + 1);
	if (!var_name)
		ft_exit(1);
	i = 0;
	while (i < index)
	{
		var_name[i] = s[i];
		i++;
	}
	var_name[i] = '\0';
	return (var_name);
}

char	*get_var_value_exp(const char *s, int index)
{
	char	*var_value;
	int		j;

	if (s[index] == '\0')
		return (NULL);
	var_value = ft_malloc2(ft_strlen_exp(s) - index + 1);
	if (!var_value)
		ft_exit(1);
	j = 0;
	while (s[index])
	{
		var_value[j] = s[index];
		index++;
		j++;
	}
	var_value[j] = '\0';
	return (var_value);
}

char	**set_words_exp(char const *s, char c)
{
	char	**tab;
	int		i;

	tab = ft_malloc2(3 * sizeof(char *));
	if (!tab)
		ft_exit(1);
	i = 0;
	while (s[i] && s[i] != c)
		i++;
	tab[0] = get_var_name_exp(s, i);
	tab[1] = get_var_value_exp(s, i + 1);
	tab[2] = NULL;
	return (tab);
}

char	**ft_split_exp(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = set_words_exp((char *)s, c);
	return (tab);
}
