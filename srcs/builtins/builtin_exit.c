/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:49:25 by modaouch          #+#    #+#             */
/*   Updated: 2019/02/01 10:02:47 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int					ft_bt_exit(char **cmd, t_list **env)
{
	int				i;
	unsigned char	ret;
	char			*to_free;

	i = 0;
	to_free = get_prompt(0);
	ft_strdel(&to_free);
	if (cmd[1])
		while (ft_isdigit(cmd[1][i]) || (cmd[1][i] == '-' || cmd[1][i] == '+'))
			i++;
	if (!cmd[1] || (!cmd[2] && i == 0))
	{
		ft_free_list(env);
		exit(EXIT_SUCCESS);
	}
	else if (!cmd[2])
	{
		ret = (unsigned char)ft_atoi(cmd[1]);
		ft_free_list(env);
		exit(ret);
	}
	else
		ft_error_message("exit", 0, 6);
	return (1);
}
