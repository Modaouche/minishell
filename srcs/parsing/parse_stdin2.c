/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_stdin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:49:25 by modaouch          #+#    #+#             */
/*   Updated: 2019/02/02 10:24:18 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_shortest_word(char *to_check)
{
	int		a;
	int		b;
	int		c;

	a = ft_strclen(to_check, ' ');
	b = ft_strclen(to_check, '\t');
	c = ft_strclen(to_check, ';');
	if (a <= b && a <= c)
		return (a);
	else if (b <= c)
		return (b);
	return (c);
}

void		ft_remove_bad_dollars(char *readed_cmd, t_list **env)
{
	t_list	*tmp;
	char	*to_find;
	int		i;

	i = 0;
	to_find = NULL;
	while (readed_cmd[i])
	{
		if (readed_cmd[i] == '$')
		{
			to_find = ft_strsub(readed_cmd, i,\
					ft_strslen(&readed_cmd[i], "\t ;/"));
			if (!(tmp = ft_list_find(*env, &to_find[1])))
				ft_memset(&readed_cmd[i], ' ',\
						ft_shortest_word(&readed_cmd[i]));
			ft_strdel(&to_find);
		}
		i++;
	}
}

char		*ft_read_stdin(void)
{
	int		ret;
	char	*command;
	char	saved[BUFFER + 1];

	if ((ret = read(STDIN_FILENO, NULL, 0)) == -1)
		exit_msg("read", 0, 6);
	if (!(command = ft_strnew(BUFFER + 1)))
		exit_msg("minishell", 0, 8);
	while ((ret = read(STDIN_FILENO, saved, BUFFER)) > 0)
	{
		if (*saved == '\n')
			break ;
		saved[ret] = 0;
		command = ft_strjoin_free(command, saved, 1);
	}
	return (command);
}
