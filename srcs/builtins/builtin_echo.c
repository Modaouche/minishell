/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:49:25 by modaouch          #+#    #+#             */
/*   Updated: 2019/01/30 20:42:39 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void		ft_print_echo(char **arg)
{
	int			i;

	i = 0;
	while (arg[i])
	{
		ft_putstr(arg[i++]);
		if (arg[i])
			ft_putchar(' ');
	}
}

static void		ft_cmp(int *op, char *arg, int no_op)
{
	(!ft_strcmp(arg, "-n") && !*op && no_op != 10) ? *op = 1 : 0;
	(!ft_strcmp(arg, "-e") && !*op && no_op != 10) ? *op = 2 : 0;
	(!ft_strcmp(arg, "-e") && (*op != 2) && no_op != 10) ? *op = 3 : 0;
	(!ft_strcmp(arg, "-n") && (*op != 1) && no_op != 10) ? *op = 3 : 0;
}

int				ft_bt_echo(char **cmd)
{
	int			i;
	int			no_op;
	int			op;

	i = 1;
	no_op = 0;
	op = 0;
	while (cmd[i])
	{
		ft_cmp(&op, cmd[i], no_op);
		if (no_op || (ft_strcmp(cmd[i], "-n") && ft_strcmp(cmd[i], "-e")))
		{
			if ((ft_strcmp(cmd[i], "-n") && ft_strcmp(cmd[i], "-e")))
			{
				ft_print_echo(&cmd[i]);
				break ;
			}
			no_op = 10;
		}
		i++;
	}
	if (!no_op && (op == 2 || !op))
		ft_putendl("");
	return (1);
}
