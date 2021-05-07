/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 21:18:57 by ahmcherk          #+#    #+#             */
/*   Updated: 2019/12/30 02:41:24 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_dblstrlen(char **str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**ft_strdbldup(char **str)
{
	int		i;
	char	**dup;

	if (!str)
		return (NULL);
	i = 0;
	if (!(dup = (char **)malloc(sizeof(char *) * (ft_dblstrlen(str) + 1))))
		return (NULL);
	while (str[i])
	{
		dup[i] = ft_strdup(str[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

int		ft_charn(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int		ft_linemanager(void)
{
	int		i;
	int		bal;
	int		sign;

	i = -1;
	bal = 0;
	sign = 0;
	while (g_line[++i])
		ft_quote(&g_line[i], &bal, &sign);
	if (bal)
	{
		ft_putstr_fd("Unmatched ", 2);
		if (bal == 2)
			ft_putchar_fd('"', 2);
		else
			ft_putchar_fd('\'', 2);
		ft_putendl_fd(".", 2);
		ft_strdel(&g_line);
		return (-1);
	}
	if (sign)
		ft_quoteline();
	return (0);
}

void	ft_unsetenv(char **tab, char ***env_cpy, int *count)
{
	char	**dbl;
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (tab[++i])
	{
		if (ft_env(tab[i], *env_cpy) != -1)
		{
			tmp = (*env_cpy)[ft_env(tab[i], *env_cpy)];
			(*env_cpy)[ft_env(tab[i], *env_cpy)] = ft_strdup("\t");
			ft_strdel(&tmp);
			j++;
		}
	}
	*count = *count - j;
	if (!(dbl = (char **)malloc(sizeof(char *) * (*count + 1))))
		return ;
	ft_delvar(env_cpy, dbl);
	ft_strdbldel(env_cpy);
	*env_cpy = dbl;
}
