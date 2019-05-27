/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:49:25 by modaouch          #+#    #+#             */
/*   Updated: 2019/02/01 05:16:40 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			ft_bt_unsetenv(char **cmd, t_list **env)
{
	int		ac;

	if (!(ac = ft_arglen(cmd)))
		ft_error_message("unsetenv", 0, 7);
	else
	{
		ac = 1;
		while (cmd[ac])
		{
			ft_list_remove_if_c(env, cmd[ac], '=');
			ac++;
		}
	}
	return (1);
}
