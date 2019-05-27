/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:49:25 by modaouch          #+#    #+#             */
/*   Updated: 2019/02/01 09:17:38 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	print_prompt(char bt, char **buff, int *len, t_list *pwd_link)
{
	if (bt == 1)
	{
		ft_printf("\e[1;32mMohashell\033[0m $> ");
		get_prompt("\e[1;32mMohashell\033[0m");
	}
	else
	{
		ft_printf("%s $> ", ft_strcat(*buff,\
			pwd_link->var_elem + (len[1] + 4)));
		get_prompt(*buff);
	}
	ft_strdel(buff);
}

static void		ft_prompt(t_list *env)
{
	t_list		*pwd_link;
	t_list		*home_link;
	int			len[2];
	char		*buff;

	pwd_link = ft_list_find(env, "PWD");
	len[0] = (pwd_link) ? ft_strlen(pwd_link->var_elem + 4) : 0;
	home_link = ft_list_find(env, "HOME");
	len[1] = (home_link) ? ft_strlen(home_link->var_elem + 5) : 0;
	if (!(buff = ft_memalloc(len[0] + 23)))
		exit_msg("minishell", 0, 8);
	if (!len[0])
		return (print_prompt(1, &buff, 0, 0));
	ft_strcpy(buff, "\e[1;32mMohashell\033[0m ~");
	if (home_link && pwd_link\
		&& !ft_strncmp(home_link->var_elem + 5, pwd_link->var_elem + 4, len[1]))
		return (print_prompt(0, &buff, len, pwd_link));
	buff[21] = 0;
	(pwd_link) ? ft_printf("%s%s $> ", buff, pwd_link->var_elem + 4)\
		: ft_printf("%s $> ", buff);
	(pwd_link) ? get_prompt(ft_strcat(buff, pwd_link->var_elem + 4))
		: get_prompt(buff);
	ft_strdel(&buff);
}

int				main(int ac, char **av, char **envp)
{
	char		***cmd;
	t_list		*list_env;
	int			i;

	(void)ac;
	(void)av;
	signal_handle(1);
	list_env = ft_tab_to_list(envp);
	ft_add_starter_var(&list_env);
	ft_add_shlvl(&list_env);
	while (42)
	{
		i = 0;
		ft_prompt(list_env);
		if (!(cmd = ft_parse_stdin(&list_env, 0, 0)))
			continue ;
		while (cmd[i])
			ft_exec_cmd(cmd[i++], &list_env);
		signal_handle(1);
		free_cmd(&cmd);
	}
	return (0);
}
