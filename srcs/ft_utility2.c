/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 17:05:46 by modaouch          #+#    #+#             */
/*   Updated: 2019/02/01 09:30:56 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char			*get_prompt(const char *curr_prompt)
{
	static char	*prompt = NULL;

	if (!curr_prompt)
		return (prompt);
	if (!prompt)
		prompt = ft_strjoin(curr_prompt, " $> ");
	else if (ft_strcmp(curr_prompt, prompt))
	{
		ft_strdel(&prompt);
		prompt = ft_strjoin(curr_prompt, " $> ");
	}
	return (prompt);
}

int				is_in_exec(char c)
{
	static int	bt = 0;

	if (c != 2)
		bt = (int)c;
	return (bt);
}

int				tab_strslen(const char **tab, const char *s)
{
	int			i;
	int			len;
	int			z;

	i = 0;
	len = 0;
	while (tab && tab[i] != NULL)
	{
		z = 0;
		while (tab[i][z])
		{
			if (ft_strslen(&tab[i][z], s))
			{
				len++;
				break ;
			}
			z++;
		}
		i++;
	}
	return (len);
}

int				ft_arglen(char **arg)
{
	int			i;

	i = 0;
	if (!arg || !*arg)
		return (0);
	while (arg[i])
		i++;
	return (i);
}

void			free_cmd(char ****cmd)
{
	int			i;
	char		***tmp;

	i = 0;
	tmp = *cmd;
	if (!cmd || !*cmd)
		return ;
	while (tmp[i])
		ft_freetab_str(&tmp[i++]);
	free(*cmd);
	tmp = NULL;
}
