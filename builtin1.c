/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 15:47:39 by ahmcherk          #+#    #+#             */
/*   Updated: 2020/01/07 23:18:28 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char ***tab)
{
	int		i;

	i = 0;
	while ((*tab)[++i])
	{
		ft_putstr((*tab)[i]);
		if ((*tab)[i + 1])
			ft_putchar(' ');
	}
	ft_putchar('\n');
}

int		builtin_manager(char ***tab, char ***env_cpy, int *count)
{
	int		i;

	i = -1;
	if (!(*tab)[0])
		return (1);
	if (!ft_strcmp((*tab)[0], "cd"))
		ft_cd(env_cpy, tab, count);
	else if (!ft_strcmp((*tab)[0], "unsetenv"))
		ft_unsetenv((*tab), env_cpy, count);
	else if (!ft_strcmp((*tab)[0], "setenv"))
		ft_setenv((*tab), env_cpy, count);
	else if (!ft_strcmp((*tab)[0], "env"))
	{
		while ((*env_cpy)[++i])
			ft_putendl((*env_cpy)[i]);
	}
	else if (!ft_strcmp("echo", (*tab)[0]))
		ft_echo(tab);
	else
		return (0);
	ft_strdbldel(tab);
	return (1);
}

int		ft_patherror(t_var *var)
{
	struct stat		st;

	if (!ft_strcmp(var->tab[0], "exit"))
		exit(0);
	if (ft_strchr(var->tab[0], '/'))
	{
		lstat(var->tab[0], &st);
		if (S_ISDIR(st.st_mode))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(var->tab[0], 2);
			ft_putendl_fd(": is a directory", 2);
			if (var->tab && *var->tab)
				ft_strdbldel(&var->tab);
			return (0);
		}
	}
	return (1);
}

DIR		**save_dir(int option)
{
	static DIR *dirp = NULL;

	if (option == 0 && dirp)
	{
		closedir(dirp);
		dirp = NULL;
	}
	return (&dirp);
}

DIR		*ft_tab(char old_c, char ***shell, int *j, int *s)
{
	struct dirent	*rd;
	DIR				**op;
	char			*str;

	rd = NULL;
	op = save_dir(1);
	if (!*s && !ft_strchr(g_line, '/'))
		ft_shellfinder(*shell, old_c, j, op);
	else
	{
		if (ft_openmanager(old_c, op, &str))
			return (NULL);
		while ((rd = readdir(*op)))
		{
			if ((!str && ft_strcmp(rd->d_name, ".") && ft_strcmp(rd->d_name
			, "..")) || (ft_strnstr(rd->d_name, str, ft_strlen(str)) &&
			ft_strcmp(rd->d_name, ".") && ft_strcmp(rd->d_name, "..")))
				break ;
		}
		ft_strdel(&str);
		if (!rd)
			return (NULL);
		ft_newline(j, rd);
	}
	return (*op);
}
