/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 14:45:03 by ahmcherk          #+#    #+#             */
/*   Updated: 2020/01/07 23:02:39 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_env(char *str, char **environ)
{
	int				i;
	int				len;

	i = 0;
	len = ft_dblstrlen(environ);
	while (i < len)
	{
		if (environ[i][ft_strlen(str)] == '=' &&
		ft_strnstr(environ[i], str, ft_strlen(str)))
			return (i);
		i++;
	}
	return (-1);
}

void	ft_putprompt(void)
{
	char	*tmp;

	tmp = NULL;
	ft_putstr(MAGENTA);
	if ((tmp = getcwd(NULL, 0)))
		ft_putstr(ft_strrchr(tmp, '/') + 1);
	ft_putstr(" > ");
	ft_putstr(RESET);
	if (tmp)
		ft_strdel(&tmp);
}

char	*ft_cmdchr(char **shell, char **tab)
{
	char	*cmd;
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!shell)
		return (NULL);
	while (shell[++i])
	{
		j = 0;
		if (!i)
			j = 5;
		if (!(shell[i][j]))
			return (NULL);
		cmd = ft_strjoin(shell[i] + j, "/");
		tmp = cmd;
		cmd = ft_strjoin(cmd, tab[0]);
		ft_strdel(&tmp);
		if (!access(cmd, X_OK | F_OK))
			return (cmd);
		ft_strdel(&cmd);
	}
	return (NULL);
}

int		ft_puterror(char **str)
{
	if (str[2])
	{
		ft_putstr("cd: string not in pwd: ");
		ft_putendl_fd(str[1], 2);
		return (1);
	}
	return (0);
}

int		ft_cdtool(char **env, char ***tab, char *path)
{
	char	*tmp;

	tmp = NULL;
	if (!(*tab)[1])
	{
		if (ft_env("HOME", env) == -1)
			return (-1);
		ft_home(tab, &tmp, env);
		if (tmp)
			ft_strdel(&tmp);
		path = (*tab)[1];
	}
	else if (ft_puterror((*tab)))
		return (-1);
	else if (!ft_strcmp((*tab)[1], "-"))
	{
		if (ft_env("OLDPWD", env) == -1)
			return (-1);
		ft_strdel(&(*tab)[1]);
		(*tab)[1] = ft_strdup(env[ft_env("OLDPWD", env)] + 7);
		path = (*tab)[1];
	}
	return (0);
}
