/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_strdup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 05:10:43 by modaouch          #+#    #+#             */
/*   Updated: 2019/02/01 10:18:21 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_nfree(char ***tab, int n)
{
	if (n == 0)
		return (0);
	while (n > 0)
		ft_strdel(&(*tab[n--]));
	ft_strdel(&(*tab[0]));
	if (tab || *tab)
		free(*tab);
	return (0);
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
		return (0);
	i = 0;
	while (tab[i])
	{
		if (!(new_tab[i] = ft_strdup(tab[i])))
			return (ft_nfree(&new_tab, --i));
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}
