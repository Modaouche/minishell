/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 06:13:25 by modaouch          #+#    #+#             */
/*   Updated: 2019/02/01 09:17:12 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void			ft_set_path(char *cmd_set, t_list **new_env)
{
	char			**cmd_to_set;

	cmd_to_set = ft_strsplit(cmd_set, ' ');
	ft_bt_setenv(cmd_to_set, new_env);
	ft_freetab_str(&cmd_to_set);
}

void				ft_add_shlvl(t_list **new_envp)
{
	t_list			*new_env;
	t_list			*shlvl_link;
	char			*cmd_to_set;
	int				level;

	new_env = *new_envp;
	shlvl_link = ft_list_find(new_env, "SHLVL");
	if (!(level = (ft_atoi(ft_strrchr(shlvl_link->var_elem, '=') + 1) + 1)))
		level = 1;
	cmd_to_set = ft_strjoin_free("env SHLVL=", ft_itoa(level), 2);
	ft_set_path(cmd_to_set, new_envp);
	ft_strdel(&cmd_to_set);
}

void				ft_add_starter_var(t_list **new_env)
{
	struct passwd	*pw;
	char			*home;
	char			*cwd;

	pw = getpwuid(getuid());
	if (!ft_list_find(*new_env, "PATH"))
		ft_set_path("env PATH=/bin:/usr/bin", new_env);
	if (!ft_list_find(*new_env, "SHLVL"))
		ft_set_path("env SHLVL=0", new_env);
	if (!ft_list_find(*new_env, "OLDPWD"))
		ft_set_path("env OLDPWD=", new_env);
	if (!ft_list_find(*new_env, "PWD"))
	{
		if (!(cwd = ft_strjoin_free("env PWD=", ft_bt_pwd(2), 2)))
			exit_msg("minishell", 0, 8);
		ft_set_path(cwd, new_env);
		(cwd) ? ft_strdel(&cwd) : 0;
	}
	if (!ft_list_find(*new_env, "HOME"))
	{
		if (!(home = ft_strjoin("env HOME=", pw->pw_dir)))
			exit_msg("minishell", 0, 8);
		ft_set_path(home, new_env);
		(home) ? ft_strdel(&home) : 0;
	}
}
