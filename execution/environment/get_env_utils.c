/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 08:55:47 by ataji             #+#    #+#             */
/*   Updated: 2022/11/10 18:23:50 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_env(char const *s1, char const *s2)
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
	sl1 = ft_strlen_env(s1);
	sl2 = ft_strlen_env(s2);
	str = (char *)malloc((sl1 + sl2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
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

int	ft_strcmp_env(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	count_words_env(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (*str)
	{
		if (*str != c && count == 0)
		{
			count = 1;
			i++;
		}
		else if (*str == c)
			count = 0;
		str++;
	}
	return (i);
}

char	**ft_freeing_env(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

char *get_var_name_env(const char *s, int index)
{
	char	*var_name;
	int		i;

	var_name = malloc(index + 1);
	if (!var_name)
		return (NULL);
	i = 0;
	while(i < index)
	{
		var_name[i] = s[i];
		i++;
	}
	var_name[i] = '\0';
	return (var_name);
}

char *get_var_value_env(const char *s, int index)
{
	char	*var_value;
	int		j;

	if(s[index] == '\0')
		return(NULL);
	var_value = malloc(ft_strlen_env(s) - index + 1);
	if(!var_value)
		return (NULL);
	j = 0;
	while(s[index])
	{
		var_value[j] = s[index];
		index++;
		j++;
	}
	var_value[j] = '\0';
	return(var_value);
	
}

char	**set_words_env(char const *s, char c)
{
	char	**tab;
	int		i;

	tab = malloc(3 * sizeof(char *));
	if(!tab)
		return(NULL);
	i = 0;
	while(s[i] && s[i] != c)
		i++;
	tab[0] = get_var_name_env(s, i);
	tab[1] = get_var_value_env(s, i + 1);
	tab[2] = NULL;
	return(tab);
}

char	**ft_split_env(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = set_words_env((char *)s, c);
	return (tab);
}
