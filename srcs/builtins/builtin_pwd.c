/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 05:13:10 by modaouch          #+#    #+#             */
/*   Updated: 2019/02/01 05:13:44 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char		*ft_bt_pwd(int bt)
{
	char	cwd[PATH_MAX];

	if (bt == 1)
	{
		if (getcwd(cwd, PATH_MAX))
			ft_printf("%s\n", cwd);
		else
			ft_error_message("pwd", 0, 6);
	}
	if (bt == 2)
	{
		if (getcwd(cwd, PATH_MAX))
			return (ft_strdup(cwd));
		else
			ft_error_message("getcwd", 0, 6);
	}
	return (0);
}

int			ft_bt_pwd_print(int bt)
{
	ft_bt_pwd(bt);
	return (1);
}
