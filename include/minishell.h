/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:09:15 by wsallei           #+#    #+#             */
/*   Updated: 2020/11/16 20:19:14 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>

# include <signal.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <limits.h>
# include "../libft/libft.h"

typedef	struct		s_tmp
{
	int				i;
	int				j;
	int				eq;
	int				st;
}					t_tmp;

typedef	struct		s_pipe
{
	int				i;
	int				cp;
	pid_t			*pid;
	int				**pipefd;
}					t_pipe;

typedef	struct		s_arg
{
	int				quote;
	char			*sarg;
	struct s_arg	*next;
	struct s_arg	*prev;
}					t_arg;

typedef	struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef	struct		s_rdir
{
	int				type;
	char			*prdir;
	struct s_rdir	*next;
}					t_rdir;

typedef	struct		s_tok
{
	int				qfunc;
	int				rdir;
	int				tsep;
	char			*prdir;
	char			*func;
	t_rdir			*ndir;
	t_arg			*arg;
	struct s_tok	*next;
	struct s_tok	*prev;
}					t_tok;

typedef	struct		s_sig
{
	int				ctc;
	int				cts;
	int				excode;
	pid_t			pid;
}					t_sig;

typedef	struct		s_config
{
	int				err;
	int				in;
	int				out;
	int				pipein;
	int				pipeout;
	int				savein;
	int				saveout;
	int				exit;
	int				excode;
	int				child;
	char			**env;
	t_pipe			pipe;
	t_env			*envl;
	t_env			*senvl;
	t_tok			*tok;
	t_env			*senv;
}					t_config;
/*
**PARSER
*/
int					close_quote(char *line);
int					checkunexp(t_config *cnf, char *line);
int					issep(char c);
int					skipsep(t_tok *tok, char *line, int i);
int					redir(char *line, int i, t_tok *tok);
void				init(t_config *cnf, char **env);
void				envtolist(t_config *cnf, char **env, int type);
int					isredir(char c);
int					checkq(char *line, int i, int eq);
int					getpth(t_rdir *tmp, char *line, int i);
int					addredir(t_tok *tok, int i, char *line);
t_tok				*analys(char *line);
t_arg				*getarg(char *line, int *i);
int					funcname(char *line, int i, t_tok *tok);
void				freeenvl(t_env *env);
void				freetok(t_tok *tok);
int					specstrlenn(char *s, t_env *env, t_config *cnf);
int					cherrdir(char *line, t_config *cnf);
int					chckqte(char *line, int i, t_tmp *tmp, int type);
/*
**EXIT
*/
void				ft_exit(t_config *cnf, char **targ);
/*
**EXECUTE
*/
char				*getname(t_config *cnf, t_tok *pnt);
void				ptenv(char *str, t_env *env, t_tmp *tmp, char *s);
int					specstrlen(char *s, t_config *cnf);
char				*namefunc(t_config *cnf, t_tok *pnt, int len);
char				*getstr(t_arg *arg, t_config *cnf);
char				*gettruepth(char *str, t_config *cnf);
int					pipedir(t_tok *pnt, t_config *cnf);
void				exec(t_config *cnf);
void				preex(t_config *cnf, t_tok *pnt);
int					goexec(t_config *cnf, t_tok *pnt, char **targ);
int					bin(char *p, char **targ, t_config *cnf);
t_tok				*gopipe(t_tok *pnt, t_config *cnf);
void				intil(t_config *cnf, t_tok *pnt);
int					inp(t_config *cnf, t_tok *pnt);
int					dir(t_config *cnf, t_tok *pnt);
void				tif(int	**tab);
void				tf(char **tab);
int					countargs(t_arg *arg);
int					lenenv(t_env *env);
t_env				*freeenv(t_env *env);
/*
**FDS
*/
void				savefd(t_config *cnf);
void				closefd(int fd);
void				closefds(t_config *cnf);
void				resetfds(t_config *cnf);
void				resfds(t_config *cnf);
/*
**BUILTINS
*/
int					gobuiltin(t_config *cnf, char **targ);
int					isbuilt(char *name);
int					ft_cd(char **argv, char **environ);
int					ft_echo(char **argv);
int					ft_env(char **environ);
int					ft_export(char **argv, t_config *cnf);
int					ft_pwd(void);
int					ft_unset(char **argv, t_config *cnf);
int					compare_str(const char *s1, const char *s2);
t_list				*get_sorted_list(t_list *env_list);
t_list				*list_from_environ(char **environ);
void				add_env(t_list *env_list, t_env *env);
t_env				*init_env(char **key_value);
void				ft_signalc(int signal);
void				ft_signals(int signal);
char				**list_to_array(t_list *list);
int					ft_strlen2(char **array);
int					siseen(t_config *cnf);
void				freed3(t_env *tenv, t_env *tenv2, int j, int remove);
void				freed2(t_env *tenv, t_env *tenv2, t_config *cnf);
void				freed(t_env *tenv, t_env *tenv2, int i, int j);
int					siseenv(t_config *cnf);
int					env_exist(char *argv, t_config *cnf);
void				remove_env(char *argv, t_config *cnf);
void				remove_env2(char *argv, t_config *cnf);
void				freed22(t_env *tenv, t_env *tenv2, t_config *cnf);
void				preexp(char **key_value, t_config *cnf);
void				postex(t_list	*env_list, t_config *cnf);
void				freelistenv(t_list *env_list);
void				re_env2(char *argv, t_config *cnf);
/*
**TEST
*/
int					checkqq(char *line, int i, int eq, t_tmp *tmp);
void				ccn(char *line, t_tmp *tmp, int i, int type);
void				checkslh(char *line, int i, t_tmp *tmp);
int					checslash(char *line, int i, t_tmp *tmp, int count);
char				**cpyenv(t_config *cnf);
void				addtoenvl(t_config *cnf, char **key_value);
extern	t_sig	g_sig;
#endif
