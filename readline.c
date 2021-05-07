/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 16:07:38 by ahmcherk          #+#    #+#             */
/*   Updated: 2020/01/07 23:23:22 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delchar(void)
{
	ft_putchar(8);
	ft_putchar(127);
	ft_putchar(8);
}

int		ft_printchar(int *s, char *c, int *j, char **old_line)
{
	char	*tmp;

	*j = *j + 1;
	tmp = g_line;
	g_line = ft_strjoin(g_line, c);
	ft_strdel(&tmp);
	if (c[0] == ' ')
	{
		if (!*s)
			*s = ft_strlen(g_line);
		tmp = *old_line;
		*old_line = ft_strjoin(*old_line, g_line);
		ft_strdel(&tmp);
		ft_strdel(&g_line);
		g_line = ft_strnew(0);
	}
	ft_putchar(c[0]);
	return (0);
}

void	ft_setdel(char **old_line)
{
	char	*tmp;

	if (ft_strlen(g_line) < 1)
	{
		tmp = *old_line;
		*old_line = ft_strsub(*old_line, 0, ft_strlen(*old_line) - 1);
		ft_strdel(&tmp);
	}
	else
	{
		tmp = g_line;
		g_line = ft_strsub(g_line, 0, ft_strlen(g_line) - 1);
		ft_strdel(&tmp);
	}
}

int		ft_inputmanager(char *c, char **old_line, int *j, int *s)
{
	t_v		v;

	v.i = 0;
	if (c[0] == '\n')
	{
		v.tmp = g_line;
		g_line = ft_strjoin(*old_line, g_line);
		ft_strdel(&v.tmp);
		ft_strdel(&(*old_line));
		*j = 0;
		ft_putchar('\n');
		return (1);
	}
	else if (ft_isprint(c[0]))
		v.i = ft_printchar(s, c, j, old_line);
	else if (c[0] == 127 && *j > 0)
	{
		v.i = 0;
		*j = *j - 1;
		if (*s >= *j)
			*s = 0;
		ft_delchar();
		ft_setdel(old_line);
	}
	return (0);
}

void	readcmd(char **env)
{
	t_readcmd	var;

	ft_readinit(&var);
	if (ft_env("PATH", env) != -1)
		var.shell = ft_strsplit(env[ft_env("PATH", env)], ':');
	else
		var.shell = (char **)ft_memalloc(sizeof(char *));
	while (1)
	{
		read(0, var.c, 1);
		var.c[1] = '\0';
		if (var.c[0] == '\t')
		{
			if (!(var.op = ft_tab(var.old_c, &var.shell, &var.j, &var.s)))
				continue ;
		}
		else if (ft_inputmanager(var.c, &var.old_line, &var.j, &var.s))
		{
			var.op = *save_dir(0);
			ft_strdbldel(&var.shell);
			break ;
		}
		var.old_c = var.c[0];
	}
}
