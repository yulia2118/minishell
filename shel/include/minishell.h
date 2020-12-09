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
	int				ctd;
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
	pid_t			pid;
	t_pipe			pipe;
	t_env			*envl;
	t_sig			sig;
	t_tok			*tok;
}					t_config;
t_config	cnf;
t_tok				*analys(char *line);
int					skipsep(t_tok *tok, char *line, int i);
int					redir(char *line, int i, t_tok *tok);
int					issep(char c);
void				exec(t_config *cnf);
int					inp(t_config *cnf, t_tok *pnt);
int					dir(t_config *cnf, t_tok *pnt);
void				resfds(t_config *cnf);
int					countargs(t_arg *arg);
void				init(t_config *cnf, char **env);
int					lenenv(t_env *env);
char				*getstr(t_arg *arg, t_env *env, t_config *cnf);
int					goexec(t_config *cnf, t_tok *pnt, char **targ);
void				tf(char **tab);
int					gobuiltin(t_config *cnf, t_tok *pnt, char **targ);
int					isbuilt(char *name);
void				closefd(int fd);
void				closefds(t_config *cnf);
void				resetfds(t_config *cnf);
void				savefd(t_config *cnf);
void				freetok(t_tok *tok);
void				freeenvl(t_env *env);
void				ft_exit(t_config *cnf, char **targ);
char				*getname(t_config *cnf, t_tok *pnt);
int					isredir(char c);
int					addredir(t_tok *tok, int i, char *line);
t_tok				*gopipe(t_tok *pnt, t_config *cnf);
int					pipedir(t_tok *pnt, t_config *cnf);
void				tif(int	**tab);
t_env				*freeenv(t_env *env);
void				envtolist(t_config *cnf, char **env);
int					getpth(t_rdir *tmp, char *line, int i);
int					checkq(char *line, int i, int eq);
char				*gettruepth(char *str, t_env *env, t_config *cnf);
int					specstrlen(char *s, t_env *env, t_config *cnf);
int					ptenv(char *str, t_env *env, int i, char *s, int k);
int					specstrlenn(char *s, t_env *env, t_config *cnf);
/*
**BUILTINS
*/
int					ft_cd(char **argv, char **environ);
int					ft_echo(char **argv);
int					ft_env(char **environ);
int					ft_export(char **argv, char **environ);
int					ft_pwd(void);
int					ft_unset(char **argv, char **environ);
int					compare_str(const char *s1, const char *s2);
t_list				*get_sorted_list(t_list *env_list);
t_list				*list_from_environ(char **environ);
void				add_env(t_list *env_list, t_env *env);
t_env				*init_env(char **key_value);
void				ft_signal(int signal);

#endif
