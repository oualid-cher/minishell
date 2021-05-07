/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 14:22:05 by ahmcherk          #+#    #+#             */
/*   Updated: 2020/01/07 23:19:17 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MINISHELL_H
# define _MINISHELL_H
# include "./libft/libft.h"

char			*g_line;
typedef struct	s_var
{
	char		**env_cpy;
	char		**tab;
	char		*cmd;
	char		**shell;
	pid_t		pid;
	int			count;
	int			run;
}				t_var;
typedef struct	s_readcmd
{
	char		c[2];
	char		old_c;
	int			j;
	char		*old_line;
	char		**shell;
	int			s;
	DIR			*op;
}				t_readcmd;
typedef struct	s_dollar
{
	char	**dollar;
	int		j;
	int		k;
	char	*var;
	char	*tmp;
}				t_dollar;
typedef struct	s_v
{
	int		i;
	char	*tmp;
}				t_v;
typedef struct	s_quote
{
	int		i;
	int		j;
	char	*line;
}				t_quote;

DIR				**save_dir(int option);
int				ft_env(char *str, char **environ);
char			*ft_cmdchr(char **shell, char **tab);
void			ft_cd(char	***env, char ***tab, int *count);
int				ft_dblstrlen(char	**str);
char			**ft_strdbldup(char **str);
int				ft_charn(char *str, char c);
int				ft_linemanager(void);
void			ft_unsetenv(char **tab, char ***env_cpy, int *count);
void			ft_putprompt(void);
void			ft_var(char ***tab, char **env_cpy);
void			ft_setenv(char **tab, char ***env_cpy, int *count);
void			ft_strdbldel(char ***str);
void			ft_strdblcpy(char **dest, char **src);
void			ft_delvar(char ***env_cpy, char **dbl);
void			ft_pathmanager(char ***shell, char **env_cpy);
int				builtin_manager(char ***tab, char ***env_cpy, int *count);
char			**ft_read(char **env);
int				ft_cdtool(char **env, char ***tab, char *path);
void			ft_setpwd(char *str, char ***env, int *count);
void			ft_cdputerror(char *str);
void			ft_readline(char **env);
struct dirent	*ft_cmdcmp(DIR *op, int *j, char *str);
void			ft_delchar(void);
void			ft_shellfinder(char **shell, char old_c, int *j, DIR **op);
DIR				*ft_pathfinder(char **str);
DIR				*ft_tab(char old_c, char ***shell, int *j, int *s);
char			*ft_dollar(char **tab, char **env_cpy);
int				ft_varsplit(char **tab, char **env_cpy);
int				ft_main(t_var *var, int *run);
int				ft_patherror(t_var *var);
void			ft_cdputerror(char *str);
int				ft_openmanager(char old_c, DIR **op, char **str);
void			ft_newline(int *j, struct dirent *rd);
void			readcmd(char **env);
void			ft_end(t_var *var);
void			ft_readinit(t_readcmd *var);
void			ft_quoteline(void);
void			ft_quote(char *line, int *bal, int *sign);
char			**ft_setread(char ***tab);
int				ft_varerror(char ***tab);
void			ft_home(char ***tab, char **tmp, char **env);
#endif
