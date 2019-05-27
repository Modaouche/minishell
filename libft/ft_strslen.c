/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strslen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 18:08:39 by modaouch          #+#    #+#             */
/*   Updated: 2019/01/30 16:44:28 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				check(const char c, const char *charset)
{
	int			i;

	i = 0;
	while (charset[i] && c != charset[i])
		i++;
	if (!charset[i])
		return (0);
	return (1);
}

size_t			ft_strslen(const char *s, const char *charset)
{
	size_t		i;

	i = 0;
	while (s[i] && !check(s[i], charset))
		i++;
	return (i);
}
