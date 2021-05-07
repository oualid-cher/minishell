/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readinit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 21:09:14 by ahmcherk          #+#    #+#             */
/*   Updated: 2019/12/30 03:08:54 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_readinit(t_readcmd *var)
{
	var->old_c = 0;
	var->old_line = ft_strnew(0);
	var->j = 0;
	var->s = 0;
	var->shell = NULL;
	var->op = NULL;
}

void	ft_quoteline(void)
{
	t_quote		var;

	var.i = -1;
	var.j = 0;
	var.line = ft_strnew(ft_strlen(g_line));
	while (g_line[++var.i] && g_line[var.i] != '\t')
		var.line[var.j++] = g_line[var.i];
	while (g_line[var.i])
	{
		if (g_line[var.i] == '\t')
			while (g_line[++var.i] != '\t')
			{
				if (g_line[var.i] != '\t' && g_line[var.i] != ' ')
					var.line[var.j++] = g_line[var.i];
				if (g_line[var.i] == ' ')
					var.line[var.j++] = '\t';
			}
		else
			var.line[var.j++] = g_line[var.i];
		var.i++;
	}
	ft_strdel(&g_line);
	g_line = var.line;
}

void	ft_quote(char *line, int *bal, int *sign)
{
	if (*line == '"' && !*bal)
	{
		*sign = 2;
		*bal = 2;
		*line = '\t';
	}
	else if (*line == '"' && *bal == 2)
	{
		*line = '\t';
		*bal = 0;
	}
	if (*line == '\'' && !*bal)
	{
		*line = '\t';
		*sign = 1;
		*bal = 1;
	}
	else if (*line == '\'' && *bal == 1)
	{
		*line = '\t';
		*bal = 0;
	}
}

char	**ft_setread(char ***tab)
{
	int		i;
	int		j;

	i = -1;
	if (!(*tab) || !(*tab)[0])
	{
		if (*tab)
			free(*tab);
		return (NULL);
	}
	while ((*tab)[++i])
	{
		j = -1;
		if (ft_strchr((*tab)[i], '\t'))
			while ((*tab)[i][++j])
			{
				if ((*tab)[i][j] == '\t')
					(*tab)[i][j] = ' ';
			}
	}
	return (*tab);
}

int		ft_varerror(char ***tab)
{
	int		k;
	char	*tmp;

	k = 0;
	while ((*tab)[k])
	{
		tmp = (*tab)[k];
		(*tab)[k] = ft_strdup("");
		ft_strdel(&tmp);
		k++;
	}
	return (1);
}
