/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 15:12:48 by modaouch          #+#    #+#             */
/*   Updated: 2019/02/02 10:28:49 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		prompt(int sig)
{
	char		*prompt;

	(void)sig;
	write(1, "\b\b  \n", 6);
	if (!(prompt = get_prompt(NULL)))
		exit_msg("minishell", 0, 8);
	write(1, prompt, ft_strlen(prompt));
}

void			signal_handle(int bt)
{
	(void)bt;
	if (bt == 1)
	{
		signal(SIGINT, prompt);
		signal(SIGTERM, prompt);
		signal(SIGQUIT, prompt);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGTERM, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	signal(SIGTSTP, SIG_IGN);
	signal(SIGCONT, SIG_IGN);
}
