/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 13:43:48 by dchristo          #+#    #+#             */
/*   Updated: 2017/05/25 15:22:56 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

static int		ft_strlen(char *str)
{
	int			i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void			ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

void			*ft_memcpy(void *str1, const void *str2, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n)
	{
		((char *)str1)[i] = ((char *)str2)[i];
		i++;
	}
	return (str1);
}

void			ft_puthex(size_t n)
{
	char		c;

	if (n > 15)
	{
		ft_puthex(n / 16);
		ft_puthex(n % 16);
	}
	else
	{
		c = (n < 10) ? '0' + n : FT_HEX[n % 10];
		write(1, &c, 1);
	}
}

void			ft_putnbr(long n)
{
	char		c;

	if (n < 0)
	{
		c = '-';
		write(1, &c, 1);
		n *= -1;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		c = n % 10 + '0';
		write(1, &c, 1);
	}
	else if (n < 10)
	{
		c = n + '0';
		write(1, &c, 1);
	}
}
