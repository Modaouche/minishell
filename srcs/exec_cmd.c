/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:49:25 by modaouch          #+#    #+#             */
/*   Updated: 2019/02/01 09:17:03 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				ft_other_cmd(char **cmd, t_list **env)
{
	int			bt;

	bt = 0;
	(!ft_strcmp("env", cmd[0]) && !bt) ? bt = ft_bt_env(cmd, env) : 0;
	(!ft_strcmp("setenv", cmd[0]) && !bt) ? bt = ft_bt_setenv(cmd, env) : 0;
	(!ft_strcmp("unsetenv", cmd[0]) && !bt) ? bt = ft_bt_unsetenv(cmd, env) : 0;
	(!ft_strcmp("cd", cmd[0]) && !bt) ? bt = ft_bt_cd(cmd, env) : 0;
	(!ft_strcmp("echo", cmd[0]) && !bt) ? bt = ft_bt_echo(cmd) : 0;
	(!ft_strcmp("exit", cmd[0]) && !bt) ? bt = ft_bt_exit(cmd, env) : 0;
	(!ft_strcmp("pwd", cmd[0]) && !bt) ? bt = ft_bt_pwd_print(1) : 0;
	return ((bt == 0) ? 0 : 1);
}

int				ft_parse_path_cmd(char *cmd, int bt)
{
	struct stat	file;

	if (!access(cmd, F_OK) && access(cmd, F_OK | X_OK) == -1)
	{
		g_error_no = EACCES;
		return (0);
	}
	if (access(cmd, F_OK))
		return (0);
	if ((stat(cmd, &file)) == 0)
	{
		if (S_ISDIR(file.st_mode))
		{
			g_error_no = EISDIR;
			return (0);
		}
	}
	if (ft_strrchr(cmd, '/') && bt == 1)
		return (1);
	else if (bt == 2)
		return (1);
	return (0);
}

char			*ft_search_cmd(char *cmd, t_list *env)
{
	int			j;
	char		**paths;
	char		*check;

	j = 0;
	g_error_no = 0;
	if (!(env = ft_list_find(env, "PATH=")))
		return (ft_parse_path_cmd(cmd, 1) ? ft_strdup(cmd) : 0);
	paths = ft_strsplit(&env->var_elem[5], ':');
	while (paths[j])
	{
		check = ft_strjoin(paths[j++], "/");
		check = ft_strjoin_free(check, cmd, 1);
		if (ft_parse_path_cmd(check, 2))
			g_error_no = 0;
		if (!access(check, F_OK | X_OK) && g_error_no == 0)
		{
			ft_freetab_str(&paths);
			return (check);
		}
		if (check)
			ft_strdel(&check);
	}
	ft_freetab_str(&paths);
	return (ft_parse_path_cmd(cmd, 1) ? ft_strdup(cmd) : 0);
}

void			ft_exec_ve(char **command, t_list *env)
{
	char		*new_cmd;
	char		**env_intab;
	pid_t		pid;

	g_error_no = 0;
	if (!(new_cmd = ft_search_cmd(command[0], env)))
		return (ft_error_message("minishell", command[0], 1));
	pid = fork();
	if (pid == 0)
	{
		env_intab = ft_list_to_tabstr(env);
		if (execve(new_cmd, command, env_intab) == -1)
			exit_msg("execve", command[0], 3);
		ft_freetab_str(&env_intab);
		ft_strdel(&new_cmd);
		return ;
	}
	ft_strdel(&new_cmd);
	if (pid < 0)
		return (exit_msg("minishell", 0, 2));
	signal_handle(0);
	wait(&g_error_no);
	kill(pid, SIGTERM);
}

void			ft_exec_cmd(char **cmd, t_list **env)
{
	if (!cmd || !*cmd)
		return ;
	if (!ft_other_cmd(cmd, env))
		ft_exec_ve(cmd, *env);
}
