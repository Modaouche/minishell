/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:49:25 by modaouch          #+#    #+#             */
/*   Updated: 2019/01/30 11:06:48 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			ft_bt_setenv(char **cmd, t_list **env)
{
	int		ac;

	if (!(ac = ft_arglen(cmd)))
	{
		ft_error_message("setenv", 0, 7);
		return (1);
	}
	if (ac == 1)
		ft_print_env(*env);
	if (ac == 2)
	{
		if (!ft_strchr(cmd[1], '='))
			if (!(cmd[1] = ft_strjoin_free(cmd[1], "=", 1)))
				exit_msg("minishell", 0, 8);
		if (!ft_list_search_replace_c(env, &cmd[1], '='))
			ft_list_add(env, cmd[1]);
	}
	if (ac > 2)
		ft_error_message("setenv", 0, 5);
	return (1);
}
