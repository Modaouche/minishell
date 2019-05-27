/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:49:25 by modaouch          #+#    #+#             */
/*   Updated: 2019/02/01 10:51:39 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list		*ft_list_new(char *data)
{
	t_list	*elem;

	if (!(elem = (t_list*)malloc(sizeof(*elem))))
		exit_msg("minishell", 0, 8);
	if (!(elem->var_elem = ft_strdup(data)))
		exit_msg("minishell", 0, 8);
	elem->next = NULL;
	return (elem);
}

void		ft_list_add(t_list **list, char *data)
{
	t_list	*tmp;

	tmp = *list;
	if (!*list)
		*list = ft_list_new(data);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_list_new(data);
	}
}

t_list		*ft_list_dup(t_list **to_dup)
{
	t_list	*new_list;
	t_list	*tmp;

	tmp = *to_dup;
	new_list = NULL;
	while (tmp)
	{
		ft_list_add(&new_list, tmp->var_elem);
		tmp = tmp->next;
	}
	return (new_list);
}

void		ft_list_remove_if_c(t_list **begin_list, char *var, int c)
{
	t_list	*tmp;
	t_list	*next;

	tmp = *begin_list;
	while (tmp && !ft_strscmp(tmp->var_elem, var, c))
	{
		next = tmp->next;
		ft_strdel(&tmp->var_elem);
		free(tmp);
		tmp = next;
		*begin_list = tmp;
	}
	while (tmp && tmp->next)
	{
		if (!ft_strscmp(tmp->next->var_elem, var, c))
		{
			next = tmp->next;
			(tmp->next) ? tmp->next = tmp->next->next : 0;
			ft_strdel(&next->var_elem);
			free(next);
		}
		else if (tmp->next)
			tmp = tmp->next;
	}
}

int			ft_list_search_replace_c(t_list **list, char **var, int c)
{
	t_list	*tmp;
	char	*str;

	tmp = *list;
	str = *var;
	while (tmp)
	{
		if (!ft_strscmp(tmp->var_elem, str, c))
		{
			ft_strdel(&tmp->var_elem);
			tmp->var_elem = ft_strdup(str);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
