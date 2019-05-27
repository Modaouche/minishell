/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabstr_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 05:28:33 by modaouch          #+#    #+#             */
/*   Updated: 2019/02/01 10:53:51 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**ft_nfree(char ***tab, int n)
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

char			**ft_tab_strnew(int nb, ...)
{
	va_list		params;
	char		**tab;
	int			i;

	i = 0;
	va_start(params, nb);
	if (!(tab = (char **)malloc(sizeof(char *) * nb + 1)))
		return (0);
	while (nb-- > 0)
		if (!(tab[i++] = ft_strdup(va_arg(params, char *))))
			return (ft_nfree(&tab, i - 2));
	tab[nb] = NULL;
	va_end(params);
	return (tab);
}
