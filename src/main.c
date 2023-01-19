/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaouzi <kfaouzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 07:08:40 by kfaouzi           #+#    #+#             */
/*   Updated: 2022/11/22 12:46:36 by kfaouzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils_char_str.h"

void	token_and_exec(char *line, t_tok *tokens, t_execlst *el)
{
	char		*t;

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
			g_data.is_running = 1;
			if (g_data.exec == 1)
				mini_token_and_exec(el);
			g_data.is_running = 0;
		}
	}
}

void	desplay_shell(char *line, t_tok *tokens, t_execlst *el)
{
	(void)tokens;
	(void)el;
	while (1)
	{
		line = readline(STR_PROMPT);
		if (!line)
			msg_error("exit\n");
		if (line[0])
		{
			add_history(line);
			token_and_exec(line, NULL, NULL);
		}
		free(line);
		ft_free_inside();
	}
	ft_free_env_exp();
}

void	run_minishell(void)
{
	signal(SIGINT, stay_in_shell);
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 0;
	desplay_shell(NULL, NULL, NULL);
}

int	main(int ac, char **av, char **env)
{
	t_env	*dt;
	t_env	*dt1;

	(void)ac;
	(void)av;
	g_data.garbege = NULL;
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
