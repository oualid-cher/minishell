/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 22:52:41 by ahmcherk          #+#    #+#             */
/*   Updated: 2020/01/07 23:00:21 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_end(t_var *var)
{
	if (var->tab && *var->tab)
		ft_strdbldel(&var->tab);
	if (var->cmd)
		ft_strdel(&var->cmd);
}

void	ft_home(char ***tab, char **tmp, char **env)
{
	char	**dbl_tmp;

	*tmp = (*tab)[1];
	(*tab)[1] = ft_strdup(env[ft_env("HOME", env)] + 5);
	dbl_tmp = (char **)ft_memalloc(sizeof(char *) * 3);
	dbl_tmp[0] = (*tab)[0];
	dbl_tmp[1] = (*tab)[1];
	free(*tab);
	*tab = dbl_tmp;
}
