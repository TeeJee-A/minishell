/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaouzi <kfaouzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 07:38:32 by kfaouzi           #+#    #+#             */
/*   Updated: 2022/11/22 11:46:17 by kfaouzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H

# define PARSING_H

typedef enum s_enum
{
	WORD,
	PIPE,
	RED,
	D_QTE,
	S_QTE,
	HEREDC,
	REDOUT,
	REDIN,
	APPND,
	NON,
}t_enum;

typedef struct s_tok
{
	char			*value;
	t_enum			type;
	struct s_tok	*next;
}t_tok;

typedef struct s_red
{
	t_enum			type;
	char			*file;
	int				fd;
	int				__errno;
	int				dlmtr;
	struct s_red	*next;
}t_red;
// access
typedef struct s_execlst
{
	char				**cmd;
	t_red				*red;
	struct s_execlst	*next;
}t_execlst;

typedef struct s_env
{
	char			*var;
	char			*val;
	int				sz_var;
	int				sz_val;
	struct s_env	*next;
}t_env;

typedef struct s_gc
{
	void		*_free;
	struct s_gc	*next;
}	t_gc;

typedef struct s_exp_env
{
	void				*_free;
	struct s_exp_env	*next;
}	t_exp_env;

typedef struct s_data
{
	t_env			*g_envlst;
	t_env			*g_explst;
	t_gc			*garbege;
	t_exp_env		*garbege_exp_env;
	int				is_running;
	int				exit_status;
	char			**g_env;
	char			**g_exp;
	int				id_cat;
	int				exec;
	struct s_data	*next;
	int				first;
	int				lenenvlst;
	int				lenexplst;
	int				check_error;
	char			*fix_pwd;
}t_data;

t_data	g_data;

//for error open

int				__check_open_error(int fd, int __errno);

//free memory

void			ft_lstclear(t_tok **lst);
void			clear_execlst(t_execlst **lst);
void			free_red(t_red **red);

//tokenizer

t_tok			*lstnew(char *content, t_enum type);
int				add_tkn(t_tok **token, t_tok *new);
t_tok			*tokenizer(char *l);
int				skipword(char *line);
int				skipquotes(char *line);
int				skiptkn(char *line);

//checking syntax

int				check_str(char *l);
int				check_red(t_tok **token);
int				check_pipe(t_tok **token);
int				check_syntax(t_tok *token);
int				exist_pipe(t_tok *token);
int				help_pipe(t_tok **token);

//prepare list for execution

int				add_tknex(t_execlst **token, t_execlst **new);
char			*new_strjoin(char *s1, char *s2);
t_execlst		*get_execlst(t_tok *tkns);
t_execlst		*getred(t_execlst *e, t_tok *tok);
t_red			*getredlst(t_red *red, t_tok *tok);
t_enum			get_redtype(char *val);
t_execlst		*getcmd(t_execlst *e, char *val);
t_execlst		*init_execlst(void);

t_execlst		*expand_list(t_execlst *el);
int				add_sqt(char *line, char **expand_str);
int				add_words(char *line, char **expand_str);
int				handel_dlr(char *line, char **expand_str);
char			*expander_hrdc(char *del);
char			*_expander(char *line, int dq);
char			*expand_hrdc(int i, int j, char *name_file, char *file);
int				ft_open(t_enum type, char **file);
void			put_in_fd(char *del, int fd, int nbdel);

void			stay_in_shell(int _signal);
void			add_garbage_in(void *data);
void			signals(void);
void			*ft_malloc2(size_t size);
// void			add_to_garbege(t_gc **data, t_gc *new);
// t_gc			*ft_new_gc(void *data);
// void			*ft_malloc(size_t size);
// void			ft_free_inside(void);
// void			ft_free_env_exp(void);
// void			ft_exit(int ex);
// int			ft_red(t_execlst *el);
#endif
