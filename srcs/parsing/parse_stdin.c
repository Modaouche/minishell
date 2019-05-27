/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_stdin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:49:25 by modaouch          #+#    #+#             */
/*   Updated: 2019/02/01 09:12:19 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	swap_cmd(char **cmd, t_list *env, int i, char *to_cmp)
{
	char	*tmp;
	t_list	*to_switch;

	tmp = NULL;
	if (!to_cmp)
		exit_msg("minishell", 0, 8);
	if ((to_switch = ft_list_find(env, to_cmp)))
		if (ft_strchr(to_switch->var_elem, '=') + 1)
		{
			if (cmd[i][1] != '\0')
				tmp = (cmd[i][0] == '~') ? ft_strdup(cmd[i] + 1)\
				: ft_strdup(cmd[i] + ft_strlen(to_cmp) + 1);
			ft_strdel(&cmd[i]);
			cmd[i] = (!tmp) ? ft_strdup(ft_strchr(to_switch->var_elem, '=') + 1)
			: ft_strjoin_free(ft_strchr(to_switch->var_elem, '=') + 1, tmp, 2);
		}
	ft_strdel(&to_cmp);
}

static void	tild_dollars_env(char **cmd, t_list *env)
{
	int		i;
	int		len;

	i = 0;
	if (!cmd)
		return ;
	while (cmd[i])
	{
		if (cmd[i][0] == '~')
			swap_cmd(cmd, env, i, ft_strdup("HOME"));
		len = ft_strslen(cmd[i], "/");
		if (cmd[i][0] == '$')
			swap_cmd(cmd, env, i, ft_strsub(cmd[i], 1, len - 1));
		++i;
	}
}

static char	***ret_parse(char **readed_cmd)
{
	ft_strdel(readed_cmd);
	return (0);
}

char		***ft_parse_stdin(t_list **env, int i, int j)
{
	char	***new_cmd;
	char	**pre_cmd;
	char	*readed_cmd;
	int		len;

	if (!isatty(STDIN_FILENO))
		exit_msg("\nTTY", 0, 6);
	readed_cmd = ft_read_stdin();
	ft_remove_bad_dollars(readed_cmd, env);
	if (!(pre_cmd = ft_strsplit(readed_cmd, ';')))
		return (ret_parse(&readed_cmd));
	len = tab_strslen((const char **)pre_cmd, "\t ");
	if (!(new_cmd = (char ***)malloc(sizeof(char **) * (len + 1))))
		exit_msg("minishell", 0, 8);
	new_cmd[len] = NULL;
	len = ft_arglen(pre_cmd);
	while (i < len)
	{
		if (!(new_cmd[j] = ft_multisplit(pre_cmd[i++], "\t ")))
			continue ;
		if (new_cmd[j] && *new_cmd[j])
			tild_dollars_env(new_cmd[j], *env);
		j++;
	}
	ft_strdel(&readed_cmd);
	ft_freetab_str(&pre_cmd);
	return (new_cmd);
}
