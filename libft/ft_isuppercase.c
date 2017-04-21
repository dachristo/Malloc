/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isuppercase.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 15:26:25 by dchristo          #+#    #+#             */
/*   Updated: 2017/04/16 20:00:03 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isuppercase(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isupper(str[i]))
			return (0);
		i++;
	}
	return (1);
}
