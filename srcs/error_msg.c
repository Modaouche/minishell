/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:49:25 by modaouch          #+#    #+#             */
/*   Updated: 2019/02/02 10:20:10 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_error_message(char *cmd, char *arg, int btn)
{
	char	str_error[10];

	ft_strcpy(str_error, "minishell");
	if (cmd == NULL)
		cmd = str_error;
	if (btn == 1 && (g_error_no == EACCES))
		ft_printf("%s: permission denied: %s\n", cmd, arg);
	else if (btn == 1 && (g_error_no == ENOTDIR))
		ft_printf("%s: is not a directory: %s\n", cmd, arg);
	else if (btn == 1 && (g_error_no == EISDIR))
		ft_printf("%s: is a directory: %s\n", cmd, arg);
	else if (btn == 1 && !ft_strcmp(cmd, "cd"))
		ft_printf("%s: no such file or directory: %s\n", cmd, arg);
	else if (btn == 1)
		ft_printf("%s: command not found: %s\n", cmd, arg);
	(btn == 2) ? ft_printf("%s: fork failed\n", cmd) : 0;
	(btn == 3) ? ft_printf("%s: execve failed for: %s\n", cmd, arg) : 0;
	(btn == 4) ? ft_printf("%s: bad math expression: operator expected\
			at `%s'\n", cmd, arg) : 0;
	(btn == 5) ? ft_printf("%s: too many arguments\n", cmd) : 0;
	(btn == 6) ? ft_printf("%s: command failed\n", cmd) : 0;
	(btn == 7) ? ft_printf("%s: too few arguments\n", cmd) : 0;
	(btn == 8) ? ft_printf("%s: malloc failed\n", cmd) : 0;
}

void		exit_msg(char *cmd, char *arg, int btn)
{
	ft_error_message(cmd, arg, btn);
	exit(EXIT_FAILURE);
}
