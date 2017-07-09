/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brigoux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 19:35:08 by brigoux           #+#    #+#             */
/*   Updated: 2016/04/21 17:48:34 by brigoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strclen(const char *s, char c)
{
	size_t		len;

	if (!s)
		return (0);
	len = 0;
	while (s[len] != c && s[len])
		len++;
	return (len);
}