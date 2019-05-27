/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:49:25 by modaouch          #+#    #+#             */
/*   Updated: 2019/02/01 10:38:03 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int		ret_too_arg(void)
{
	ft_error_message("cd", 0, 5);
	return (1);
}

static void		one_dash(int opt, t_list **env)
{
	t_list		*link_env;
	char		*tmp_pwd;

	if (!(link_env = ft_list_find(*env, "OLDPWD")) || !link_env->var_elem[7])
		return ;
	tmp_pwd = ft_strdup(&link_env->var_elem[7]);
	(link_env) ? ft_change_cwd(tmp_pwd, opt, env)
		: ft_error_message("cd -", 0, 6);
	ft_strdel(&tmp_pwd);
}

static void		for_pwd(t_list **env)
{
	char		*new_pwd;
	char		**command;

	new_pwd = ft_strjoin_free("setenv PWD=", ft_bt_pwd(2), 2);
	command = ft_strsplit(new_pwd, ' ');
	ft_bt_setenv(command, env);
	ft_strdel(&new_pwd);
	ft_freetab_str(&command);
}

int				ft_bt_cd(char **cmd, t_list **env)
{
	t_list		*link_env;
	int			i;
	int			opt;

	i = 1;
	opt = 0;
	if (ft_arglen(cmd) > 3)
		return (ret_too_arg());
	(!(link_env = ft_list_find(*env, "PWD"))) ? for_pwd(env) : 0;
	while (cmd[i])
	{
		(!ft_strcmp(cmd[i], "-P") && !opt) ? opt = 1 : 0;
		if (opt > 1 || (ft_strcmp(cmd[i], "--") && ft_strcmp(cmd[i], "-P")))
		{
			(!ft_strcmp(cmd[i], "-")) ? one_dash(opt, env)\
			: ft_change_cwd(cmd[i], opt, env);
			return (1);
		}
		(!ft_strcmp(cmd[i++], "--")) ? opt += 5 : 0;
	}
	link_env = ft_list_find(*env, "HOME");
	(link_env) ? ft_change_cwd(&link_env->var_elem[5], 0, env) : 0;
	return (1);
}
