/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 07:08:40 by kfaouzi           #+#    #+#             */
/*   Updated: 2022/11/16 13:33:38 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils_char_str.h"

void token_and_exec(char *line, t_tok *tokens, t_execlst *el)
{
	char *t;
	t_execlst *el1;

	t = line;
	line = ft_strtrim(line, STR_SPC);
	tokens = tokenizer(line);
	if (!check_syntax(tokens))
	{
		el = get_execlst(tokens);
		if (el)
		{
			g_data.exec = 1;
			el = expand_list(el);
			el1 = el;
			if (g_data.exec == 1)
				mini_token_and_exec(el1);
		}
	}
}

void desplay_shell(char *line, t_tok *tokens, t_execlst *el)
{
	(void)tokens;
	(void)el;
	while (1)
	{
		line = readline(STR_PROMPT);
		if (!line)
		{
			write(1, " exit\n", 6);
			exit(0);
		}
		if (line[0])
		{
			add_history(line);
			token_and_exec(line, NULL, NULL);
		}
	}
}

void run_minishell(void)
{
	signal(SIGINT, stay_in_shell);
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 0;
	desplay_shell(NULL, NULL, NULL);
}

int my_strlendm(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int main(int ac, char **av, char **env)
{
	t_env *dt;
	t_env *dt1;

	(void)ac;
	(void)av;
	g_data.g_env = env;
	g_data.g_exp = env;
	g_data.g_envlst = init_envlst();
	g_data.g_explst = init_explst();
	dt = g_data.g_envlst;
	dt1 = g_data.g_explst;
	g_data.lenenvlst = 0;
	if (!g_data.g_env[0])
	{
		get_env_empty(dt);
		get_exp_empty(dt1);
	}
	else
	{
		get_env(dt);
		get_exp(dt1);
	}
	run_minishell();
	return (0);
}
