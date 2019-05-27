/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:49:25 by modaouch          #+#    #+#             */
/*   Updated: 2019/02/01 09:18:04 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int		add_rm_repo(int i, char *path, char **pwd_var)
{
	if (!i && path[i] == '/')
	{
		if (ft_strlen(*pwd_var) > 5)
			ft_bzero(ft_strchr(*pwd_var, '/') + 1,
			ft_strlen(ft_strchr(*pwd_var, '/')));
		i++;
	}
	else
	{
		ft_add_slash(pwd_var, ft_strcdup(&path[i], '/'));
		i += ft_strclen(&path[i], '/');
	}
	return (i);
}

static int		rollback_ddot(int i, char *path, char **new_path)
{
	char		*tmp;

	tmp = *new_path;
	if (ft_strlen(tmp) > 5)
		ft_bzero(ft_strrchr(tmp, '/'),
		ft_strlen(ft_strrchr(tmp, '/')));
	if (!tmp[4])
		tmp = ft_strjoin_free(tmp, "/", 1);
	*new_path = tmp;
	return (i + ft_strclen(&path[i], '/'));
}

static int		if_error_ret(char *path, char **new_p, int bt)
{
	char		*new_path;

	new_path = NULL;
	g_error_no = 0;
	if (bt == 1)
	{
		new_path = *new_p;
		ft_memmove(new_path, new_path + 4, ft_strlen(new_path + 4) + 1);
		ft_parse_path_cmd(new_path, 2);
		ft_strdel(&new_path);
	}
	else
		ft_parse_path_cmd(path, 2);
	if (g_error_no == EISDIR)
		return (1);
	if (g_error_no != EISDIR)
		ft_error_message("cd", path, 1);
	return (0);
}

int				ft_check_valid_path(char *path, char *new_path,\
				t_list *pwd_var, int i)
{
	ft_remove_slash(pwd_var->var_elem, 0);
	ft_remove_slash(path, 1);
	if (path[0] != '/')
	{
		(!(new_path = ft_strdup(pwd_var->var_elem)))\
		? exit_msg("minishell", 0, 8) : 0;
		while (path[i])
		{
			if (!ft_strncmp(&path[i], "..", 2))
			{
				i = rollback_ddot(i, path, &new_path);
				continue ;
			}
			if (!ft_strcmp(&path[i], ".") || !ft_strncmp(&path[i], "./", 2))
			{
				i++;
				continue ;
			}
			i = (!i || (i && path[i - 1] == '/' && path[i] != '/'))\
				? add_rm_repo(i, path, &new_path) : i + 1;
		}
		return (if_error_ret(path, &new_path, 1));
	}
	return (if_error_ret(path, NULL, 0));
}

void			ft_symb_link_path(char *path, t_list **env, int i)
{
	t_list		*pwd;

	pwd = ft_list_find(*env, "PWD");
	ft_remove_slash(pwd->var_elem, 0);
	ft_remove_slash(path, 1);
	ft_replace_var(&pwd->var_elem[4], env);
	while (path[i])
	{
		if (!ft_strncmp(&path[i], "..", 2))
		{
			i = rollback_ddot(i, path, &pwd->var_elem);
			continue ;
		}
		if (!ft_strcmp(&path[i], ".") || !ft_strncmp(&path[i], "./", 2))
		{
			i++;
			continue ;
		}
		i = (!i || (i && path[i - 1] == '/' && path[i] != '/'))\
			? add_rm_repo(i, path, &(pwd->var_elem)) : i + 1;
	}
}
