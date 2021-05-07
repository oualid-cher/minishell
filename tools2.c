/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 21:23:23 by ahmcherk          #+#    #+#             */
/*   Updated: 2019/12/30 03:10:23 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_var(char ***tab, char **env_cpy)
{
	int		i;
	char	*tmp;
	char	*var;

	i = -1;
	tmp = NULL;
	var = NULL;
	while ((*tab)[++i])
	{
		if ((*tab)[i][0] == '~')
		{
			tmp = (*tab)[i];
			if (ft_env("HOME", env_cpy) != -1)
				(*tab)[i] = ft_strjoin(env_cpy[ft_env("HOME", env_cpy)] + 5,
				(*tab)[i] + 1);
			else
				(*tab)[i] = ft_strdup("");
			ft_strdel(&tmp);
		}
		if (ft_varsplit(&(*tab)[i], env_cpy) && ft_varerror(tab))
			break ;
	}
}

void	ft_delvar(char ***env_cpy, char **dbl)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while ((*env_cpy)[++i])
	{
		if ((*env_cpy)[i][0] != '\t')
			dbl[++j] = ft_strdup((*env_cpy)[i]);
	}
	dbl[++j] = NULL;
}

void	ft_pathmanager(char ***shell, char **env_cpy)
{
	int		env;

	if (*shell)
		ft_strdbldel(shell);
	if ((env = ft_env("PATH", env_cpy)) != -1)
		*shell = ft_strsplit((env_cpy[env]), ':');
}

void	ft_cdputerror(char *str)
{
	ft_putstr_fd("cd: no such file or directory: ", 2);
	ft_putendl_fd(str, 2);
}
