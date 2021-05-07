/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 02:22:50 by ahmcherk          #+#    #+#             */
/*   Updated: 2020/01/02 16:58:47 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct dirent	*ft_cmdcmp(DIR *op, int *j, char *str)
{
	struct dirent *rd;

	while ((rd = readdir(op)) > 0)
	{
		if (ft_strnstr(rd->d_name, str, ft_strlen(str)) && rd->d_name[0] != '.')
		{
			while (*j)
			{
				ft_delchar();
				*j -= 1;
			}
			ft_strdel(&g_line);
			g_line = ft_strdup(rd->d_name);
			*j = *j + ft_strlen(g_line);
			ft_putstr(rd->d_name);
			return (rd);
		}
	}
	return (0);
}

void			ft_shellfinder(char **shell, char old_c, int *j, DIR **op)
{
	static char			*str = NULL;
	struct dirent		*rd;
	static int			i;

	if (old_c != '\t')
		i = 0;
	if (!i && old_c != '\t')
		str = ft_strdup(g_line);
	if (!str || !str[0])
		return ;
	while (shell[i])
	{
		if (old_c != '\t')
			if (i == 0)
				*op = opendir(shell[i] + 5);
		rd = ft_cmdcmp(*op, j, str);
		if (rd && !ft_strcmp(rd->d_name, g_line))
			return ;
		i++;
		closedir(*op);
		*op = opendir(shell[i]);
	}
	ft_strdel(&str);
	i = 0;
}

void			ft_setpath(char **str, char **path)
{
	if (g_line[ft_strlen(g_line) - 1] != '/')
		*path = ft_strsub(g_line, 0, ft_strlen(g_line) - ft_strlen(*str));
	else
	{
		*path = ft_strdup(g_line);
		ft_strdel(str);
		*str = ft_strdup("");
	}
}

DIR				*ft_pathfinder(char **str)
{
	char	*path;
	DIR		*op;

	op = NULL;
	if (ft_strchr(g_line, '/') &&
	(*str = ft_strdup(ft_strrchr(g_line, '/') + 1)))
		ft_setpath(str, &path);
	else
	{
		*str = ft_strdup(g_line);
		path = ft_strdup(".");
	}
	if (!access(path, X_OK | F_OK))
		op = opendir(path);
	else
	{
		ft_strdel(&path);
		return (NULL);
	}
	ft_strdel(&path);
	return (op);
}

void			ft_newline(int *j, struct dirent *rd)
{
	int		i;
	char	*tmp;

	i = ft_strlen(g_line);
	while (--i >= 0 && g_line[i] != '/')
	{
		ft_delchar();
		*j -= 1;
	}
	ft_putstr(rd->d_name);
	tmp = g_line;
	g_line = ft_strsub(g_line, 0, i + 1);
	ft_strdel(&tmp);
	tmp = g_line;
	g_line = ft_strjoin(g_line, rd->d_name);
	ft_strdel(&tmp);
	*j = *j + (int)ft_strlen(rd->d_name);
}
