/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 01:27:46 by dchristo          #+#    #+#             */
/*   Updated: 2016/07/14 20:56:11 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	long l;

	l = (long)n;
	if (l < 0)
	{
		ft_putchar('-');
		l *= -1;
	}
	if (l >= 10)
	{
		ft_putnbr(l / 10);
		ft_putchar(l % 10 + '0');
	}
	else if (l < 10)
	{
		ft_putchar(l + '0');
	}
}
