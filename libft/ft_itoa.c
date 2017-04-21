/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 01:00:21 by dchristo          #+#    #+#             */
/*   Updated: 2017/04/16 20:01:24 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

static int		ft_intlen(long n)
{
	int len;

	len = 1;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static long		ft_isneg(long l, int *neg)
{
	if (l < 0)
	{
		*neg = 1;
		l = l * -1;
	}
	else
		*neg = 0;
	return (l);
}

char			*ft_itoa(int n)
{
	char	*dest;
	int		len;
	int		neg;
	long	l;

	l = (long)n;
	l = ft_isneg(l, &neg);
	len = ft_intlen(l);
	if ((dest = ft_strnew(len)) == NULL)
		return (NULL);
	dest[len] = '\0';
	if (neg != 1 && l != 0)
		len--;
	len--;
	while (len != -1)
	{
		if (neg == 1 && len == 0)
			dest[len--] = '-';
		else
		{
			dest[len--] = l % 10 + '0';
			l = l / 10;
		}
	}
	return (dest);
}
