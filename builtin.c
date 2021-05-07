/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 01:08:04 by ahmcherk          #+#    #+#             */
/*   Updated: 2019/12/28 22:39:26 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strdbldel(char ***str)
{
	int i;

	i = -1;
	if (!(*str))
		return ;
	while ((*str)[++i])
		ft_strdel(&(*str)[i]);
	ft_strdel(&(*str)[i]);
	free(*str);
	*str = NULL;
}

void	ft_strdblcpy(char **dest, char **src)
{
	int i;

	i = -1;
	while (src[++i])
		dest[i] = ft_strdup(src[i]);
	dest[i] = NULL;
}

void	ft_fill(char **tmp)
{
	char	*tmp2;

	tmp2 = *tmp;
	*tmp = ft_strjoin("=", *tmp);
	ft_strdel(&tmp2);
}

void	ft_fill2(char **tmp, char *str)
{
	char	*tmp2;

	tmp2 = *tmp;
	*tmp = ft_strjoin(*tmp, str);
	ft_strdel(&tmp2);
}

void	ft_setenv(char **tab, char ***env_cpy, int *count)
{
	int		j;
	char	*tmp;
	char	**dbltmp;

	if (!tab[1] || ft_env(tab[1], *env_cpy) != -1)
		return ;
	if (!tab[2])
		tab[2] = ft_strnew(0);
	j = 2;
	tmp = ft_strdup(tab[2]);
	while (tab[++j])
		ft_fill2(&tmp, tab[j]);
	ft_fill(&tmp);
	dbltmp = (char **)malloc(sizeof(char *) * (*count + 2));
	ft_strdblcpy(dbltmp, *env_cpy);
	dbltmp[*count] = ft_strjoin(tab[1], tmp);
	dbltmp[*count + 1] = NULL;
	ft_strdbldel(env_cpy);
	*env_cpy = dbltmp;
	*count += 1;
	ft_strdel(&tmp);
}
