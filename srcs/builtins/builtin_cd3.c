/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:49:25 by modaouch          #+#    #+#             */
/*   Updated: 2019/02/01 07:13:58 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void			ft_replace_var(char *strpwd, t_list **env)
{
	char		*tmp_cmd;
	char		**tmp_cmd_tab;

	if (!(tmp_cmd = ft_strjoin("setenv OLDPWD=", strpwd)))
		exit_msg("minishell", 0, 8);
	if (!(tmp_cmd_tab = ft_strsplit(tmp_cmd, ' ')))
		exit_msg("minishell", 0, 8);
	ft_bt_setenv(tmp_cmd_tab, env);
	ft_strdel(&tmp_cmd);
	ft_freetab_str(&tmp_cmd_tab);
}

void			ft_remove_slash(char *strpwd, int bt)
{
	int			end;
	int			begin;

	end = ft_strlen(strpwd);
	begin = (bt == 0) ? ft_strclen(strpwd, '=') : 0;
	if ((!bt && strpwd[end - 1] == '/' && (&strpwd[end - 1]
		!= &strpwd[begin + 1])) || (bt == 1
		&& (&strpwd[end - 1] != &strpwd[begin])))
	{
		while (strpwd[end - 1] == '/')
			end--;
		ft_bzero(&strpwd[end], ft_strlen(&strpwd[end]));
	}
}

void			ft_add_slash(char **src, char *to_add)
{
	int			end;
	char		*s;

	s = *src;
	end = ft_strlen(*src);
	if (s[end - 1] != '/' || ft_strcmp(&s[4], "/"))
	{
		if (!(*src = ft_strjoin_free(*src, "/", 1)))
			exit_msg("minishell", 0, 8);
		if (!(*src = ft_strjoin_free(*src, to_add, 3)))
			exit_msg("minishell", 0, 8);
	}
	else if (!(*src = ft_strjoin_free(*src, to_add, 3)))
		exit_msg("minishell", 0, 8);
}

void			ft_full_path(t_list **env)
{
	t_list		*pwd;

	pwd = ft_list_find(*env, "PWD");
	ft_replace_var(&pwd->var_elem[4], env);
	ft_strdel(&pwd->var_elem);
	if (!(pwd->var_elem = ft_bt_pwd(2)))
		return ;
	if (!(pwd->var_elem = ft_strjoin_free("PWD=", pwd->var_elem, 2)))
		exit_msg("minishell", 0, 8);
}

void			ft_change_cwd(char *path, int opt, t_list **env)
{
	t_list		*pwd_var;

	if (!(pwd_var = ft_list_find(*env, "PWD")))
		return ;
	if (!ft_check_valid_path(path, 0, pwd_var, 0))
		return ;
	ft_symb_link_path(path, env, 0);
	if ((chdir(&pwd_var->var_elem[4])) == -1)
	{
		ft_error_message("cd", 0, 6);
		return ;
	}
	if (opt == 1 || opt == 6)
		ft_full_path(env);
}
