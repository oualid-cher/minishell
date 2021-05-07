/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vartools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 04:59:22 by ahmcherk          #+#    #+#             */
/*   Updated: 2020/01/03 21:54:41 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delete(char **str)
{
	ft_strdel(str);
	*str = ft_strdup("");
}

char	*ft_dollar(char **tab, char **env_cpy)
{
	t_dollar	var;

	var.j = -1;
	var.k = 0;
	var.dollar = ft_strsplit(*tab, '$');
	var.var = NULL;
	while (var.dollar[++var.j])
		if (ft_env(var.dollar[var.j], env_cpy) == -1)
			ft_delete(&var.dollar[var.j]);
		else if (!var.k)
		{
			var.k = 1;
			var.var = ft_strdup(env_cpy[ft_env(var.dollar[var.j], env_cpy)] +
			ft_strlen(var.dollar[var.j]) + 1);
		}
		else
		{
			var.tmp = var.var;
			var.var = ft_strjoin(var.var, env_cpy[ft_env(var.dollar[var.j],
			env_cpy)] + ft_strlen(var.dollar[var.j]) + 1);
			ft_strdel(&var.tmp);
		}
	ft_strdbldel(&var.dollar);
	return (var.var);
}

int		ft_varsplit(char **tab, char **env_cpy)
{
	char	*var;

	var = NULL;
	if (ft_strchr(*tab, '$'))
	{
		if ((var = ft_dollar(tab, env_cpy)))
		{
			ft_strdel(tab);
			*tab = ft_strdup(var);
			ft_strdel(&var);
		}
		else
		{
			ft_putstr_fd(*tab + 1, 2);
			ft_putendl_fd(": Undefiend variable.", 2);
			ft_strdel(tab);
			*tab = ft_strdup("");
			return (1);
		}
	}
	return (0);
}

int		ft_openmanager(char old_c, DIR **op, char **str)
{
	if (old_c != '\t')
		*op = ft_pathfinder(str);
	if (!*op)
		return (1);
	return (0);
}

void	ft_readline(char **env)
{
	struct termios old;
	struct termios new;

	tcgetattr(STDIN_FILENO, &old);
	tcgetattr(STDIN_FILENO, &new);
	new.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, &new);
	g_line = ft_strnew(0);
	readcmd(env);
	tcsetattr(0, TCSANOW, &old);
}
