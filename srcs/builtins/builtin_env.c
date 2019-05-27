/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:49:25 by modaouch          #+#    #+#             */
/*   Updated: 2019/02/01 09:09:46 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void			ft_print_env(t_list *env)
{
	while (env)
	{
		ft_putendl(env->var_elem);
		env = env->next;
	}
}

static char		**ft_opt(t_list **new_env, char **name_value, int i)
{
	char		**new_cmd;
	t_list		*tmp;

	tmp = NULL;
	new_cmd = NULL;
	while (name_value[i] && ft_strchr(name_value[i], '='))
	{
		ft_list_add(&tmp, name_value[i]);
		i++;
	}
	if (name_value[i])
		new_cmd = ft_tab_strdup(&name_value[i]);
	else
		new_cmd = ft_strsplit("env", ' ');
	if (*new_env)
		ft_free_list(new_env);
	*new_env = tmp;
	return (new_cmd);
}

static char		**ft_not_opt(t_list **new_env, char **name_value, int i)
{
	char		**new_cmd;

	new_cmd = NULL;
	while (name_value[i] && ft_strchr(name_value[i], '='))
	{
		if (!ft_list_search_replace_c(new_env, &name_value[i], '='))
			ft_list_add(new_env, name_value[i]);
		i++;
	}
	if (name_value[i])
		new_cmd = ft_tab_strdup(&name_value[i]);
	else
		new_cmd = ft_strsplit("env", ' ');
	return (new_cmd);
}

static char		**ft_cmd_for_env(char **command, t_list **new_env)
{
	char		**new_cmd;

	new_cmd = NULL;
	if (!ft_strcmp(command[1], "-i"))
		new_cmd = ft_opt(new_env, command, 2);
	else
		new_cmd = ft_not_opt(new_env, command, 1);
	return (new_cmd);
}

int				ft_bt_env(char **cmd, t_list **env)
{
	char		**new_cmd;
	t_list		*new_env;

	if (!cmd[1])
	{
		ft_print_env(*env);
		return (1);
	}
	new_env = ft_list_dup(env);
	new_cmd = ft_cmd_for_env(cmd, &new_env);
	ft_exec_cmd(new_cmd, &new_env);
	ft_free_list(&new_env);
	if (new_cmd)
		ft_freetab_str(&new_cmd);
	return (1);
}
