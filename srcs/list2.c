/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:53:38 by modaouch          #+#    #+#             */
/*   Updated: 2019/01/30 19:05:49 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list		*ft_tab_to_list(char **env)
{
	t_list	*list;
	int		i;

	i = 0;
	list = NULL;
	while (env && env[i])
		ft_list_add(&list, env[i++]);
	return (list);
}

t_list		*ft_list_find(t_list *begin_list, char *data_ref)
{
	t_list	*seeker;
	char	*to_cmp;

	seeker = begin_list;
	while (seeker)
	{
		to_cmp = seeker->var_elem;
		if (!ft_strscmp(to_cmp, data_ref, '='))
			return (seeker);
		seeker = seeker->next;
	}
	return (0);
}

void		ft_free_list(t_list **to_remove)
{
	t_list	*tmp;
	t_list	*saved;

	saved = NULL;
	tmp = *to_remove;
	if (!to_remove || !*to_remove)
		return ;
	while (tmp)
	{
		saved = tmp;
		ft_strdel(&tmp->var_elem);
		tmp = tmp->next;
		free(saved);
	}
}
