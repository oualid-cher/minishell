/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 11:40:59 by ahmcherk          #+#    #+#             */
/*   Updated: 2019/12/30 16:25:52 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_read(char **env)
{
	char	**tab;

	ft_putprompt();
	ft_readline(env);
	if (!g_line || !g_line[0])
	{
		if (g_line)
			free(g_line);
		return (NULL);
	}
	if (ft_linemanager() == -1)
		return (NULL);
	tab = ft_strsplit(g_line, ' ');
	ft_strdel(&g_line);
	return (ft_setread(&tab));
}

char	*ft_putcmd(char ***shell, char **tab, char **env_cpy)
{
	char	*cmd;

	cmd = NULL;
	if (ft_strchr(tab[0], '/'))
	{
		if (!access(tab[0], F_OK | X_OK))
			cmd = ft_strdup(tab[0]);
		else
		{
			ft_putendl_fd("path invalid", 2);
			return (NULL);
		}
	}
	else
	{
		ft_pathmanager(shell, env_cpy);
		cmd = ft_cmdchr(*shell, tab);
	}
	if (!cmd)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putendl(tab[0]);
	}
	return (cmd);
}

int		ft_run(t_var *var)
{
	if (!var->env_cpy)
	{
		var->env_cpy = (char **)malloc(sizeof(char *));
		var->env_cpy[0] = NULL;
	}
	if (!(var->tab = ft_read(var->env_cpy)))
		return (1);
	ft_var(&var->tab, var->env_cpy);
	if (!ft_strcmp(var->tab[0], "exit"))
	{
		if (var->env_cpy)
			ft_strdbldel(&var->env_cpy);
		if (var->tab)
			ft_strdbldel(&var->tab);
		if (var->shell)
			ft_strdbldel(&var->shell);
		exit(0);
	}
	return (0);
}

int		ft_main(t_var *var, int *run)
{
	if ((*run = ft_run(var)) == 1)
		return (0);
	if (builtin_manager(&var->tab, &var->env_cpy, &var->count))
		return (0);
	if (!(var->cmd = ft_putcmd(&var->shell, var->tab, var->env_cpy)))
	{
		ft_strdbldel(&var->tab);
		return (0);
	}
	if (!ft_patherror(var))
		return (0);
	if ((var->pid = fork()) == -1)
		exit(-1);
	return (1);
}

int		main(void)
{
	extern char **environ;
	t_var		var;

	var.env_cpy = ft_strdbldup(environ);
	if (var.env_cpy)
		var.count = ft_dblstrlen(var.env_cpy);
	else
		var.count = 0;
	var.run = 0;
	while (1)
	{
		if (!ft_main(&var, &var.run))
			continue ;
		if (var.pid == 0)
		{
			if (execve(var.cmd, var.tab, var.env_cpy) == -1)
				exit(-1);
		}
		else
		{
			wait(NULL);
			ft_end(&var);
		}
	}
}
