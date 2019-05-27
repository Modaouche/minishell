/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 18:40:06 by modaouch          #+#    #+#             */
/*   Updated: 2019/02/01 09:17:17 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_strscmp(const char *s1, const char *s2, char c)
{
	while ((((*s1 == *s2) && *s1 != c) && *s1) && *s2)
	{
		s1++;
		s2++;
	}
	if ((*s1 == c && !*s2) || (*s2 == c && !*s1))
		return (0);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char		**ft_list_to_tabstr(t_list *list)
{
	char	**new_tab;
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = list;
	if (!list)
		return (0);
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	if (!(new_tab = (char **)malloc(sizeof(char *) * (i + 1))))
		exit_msg("minishell", 0, 8);
	i = 0;
	while (list)
	{
		if (!(new_tab[i] = ft_strdup(list->var_elem)))
			exit_msg("minishell", 0, 8);
		i++;
		list = list->next;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

char		**ft_tab_strdup(char **tab)
{
	char	**new_tab;
	int		i;

	i = 0;
	if (!tab || !*tab)
		return (0);
	while (tab[i])
		i++;
	if (!(new_tab = (char **)malloc(sizeof(char *) * (i + 1))))
		exit(EXIT_FAILURE);
	i = 0;
	while (tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

void		ft_printab(char **tabstr)
{
	int		i;

	i = 0;
	while (tabstr[i])
	{
		ft_printf("%s\n", tabstr[i]);
		i++;
	}
}

void		ft_freetab_str(char ***tabstr)
{
	int		i;
	char	**tmpstr;

	i = 0;
	tmpstr = *tabstr;
	if (!tabstr || !*tabstr)
		return ;
	while (tmpstr[i])
	{
		if (tmpstr[i])
			ft_strdel(&tmpstr[i]);
		i++;
	}
	free(tmpstr);
	tmpstr = NULL;
}
