/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 07:38:42 by ahmcherk          #+#    #+#             */
/*   Updated: 2020/01/02 17:28:08 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pathfill(char **path, char *str)
{
	char	*tmp;
	char	*del;

	del = getcwd(NULL, 0);
	*path = ft_strjoin(del, "/");
	ft_strdel(&del);
	tmp = *path;
	*path = ft_strjoin(*path, str);
	ft_strdel(&tmp);
}

void	ft_setpwd(char *str, char ***env, int *count)
{
	char	**tb;

	tb = (char **)malloc(sizeof(char *) * 4);
	tb[0] = ft_strdup("oualid");
	tb[1] = ft_strdup(str);
	tb[2] = ft_strdup(getcwd(NULL, 0));
	tb[3] = NULL;
	ft_setenv(tb, env, count);
	ft_strdbldel(&tb);
}

void	ft_change(char ***env, char *str)
{
	char	*tmp;
	char	*del;

	tmp = (*env)[ft_env(str, *env)];
	if (!ft_strcmp(str, "PWD"))
	{
		del = getcwd(NULL, 0);
		(*env)[ft_env(str, *env)] = ft_strjoin("PWD=", del);
	}
	else
	{
		del = getcwd(NULL, 0);
		(*env)[ft_env(str, *env)] = ft_strjoin("OLDPWD=", del);
	}
	ft_strdel(&del);
	ft_strdel(&tmp);
}

int		ft_check(char ***env, char ***tab, char **path)
{
	if (ft_cdtool(*env, tab, *path) == -1)
		return (0);
	if (!ft_strcmp((*tab)[1], "..") || (*tab)[1][0] == '/')
		*path = ft_strdup((*tab)[1]);
	else
		ft_pathfill(path, ((*tab)[1]));
	return (1);
}

void	ft_cd(char ***env, char ***tab, int *count)
{
	char	*path;
	char	*del;

	path = NULL;
	if (!ft_check(env, tab, &path))
		return ;
	if (!access(path, F_OK | X_OK) && ft_strcmp((*tab)[1], "."))
	{
		ft_strdel(&(*tab)[1]);
		(*tab)[1] = path;
		if (ft_env("OLDPWD", *env) == -1)
			ft_setpwd("OLDPWD", env, count);
		else if ((del = getcwd(NULL, 0)))
			ft_change(env, "OLDPWD");
		ft_strdel(&del);
		chdir(path);
		if (ft_env("PWD", *env) == -1)
			ft_setpwd("PWD", env, count);
		else if ((del = getcwd(NULL, 0)))
			ft_change(env, "PWD");
		ft_strdel(&del);
	}
	else
		ft_cdputerror((*tab)[1]);
}
