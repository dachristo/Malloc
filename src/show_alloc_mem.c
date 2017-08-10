/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 13:49:53 by dchristo          #+#    #+#             */
/*   Updated: 2017/08/10 17:31:37 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

static void			ft_putdata(t_region_d *data)
{
	ft_putstr("0x");
	ft_puthex((size_t)data->data);
	ft_putstr(" - ");
	ft_putstr("0x");
	ft_puthex((size_t)(data->data + data->len));
	ft_putstr(" : ");
	ft_putnbr(data->len);
	ft_putstr(" octects ");
	printf(" - %d\n", data->isfree);
	//ft_putstr("\n");
}

static void			show_tiny_mem(t_region_d *data)
{
	ft_putstr("TINY : ");
	ft_putstr("0x");
	ft_puthex((size_t)data);
	ft_putstr("\n");
	while (data != NULL)
	{
		if (data->isfree != 2)
			ft_putdata(data);
		data = data->next;
	}
}

static void			show_small_mem(t_region_d *data)
{
	ft_putstr("SMALL : ");
	ft_putstr("0x");
	ft_puthex((size_t)data);
	ft_putstr("\n");
	while (data != NULL)
	{
		if (data->isfree != 2)
			ft_putdata(data);
		data = data->next;
	}
}

static void			show_large_mem(t_region_d *data, t_alloc *alloc)
{
	ft_putstr("LARGE : ");
	ft_putstr("0x");
	ft_puthex((size_t)data);
	ft_putstr("\n");
	while (data != NULL)
	{
		ft_putdata(data);
		data = data->next;
	}
	ft_putstr("Total : ");
	ft_putnbr((SMALL * alloc->total_s_used + alloc->size_s_used) +
			(TINY * alloc->total_t_used + alloc->size_t_used) +
			(alloc->size_l_used));
	ft_putstr(" octects\n");
}

void				show_alloc_mem(void)
{
	t_alloc			*alloc;

	alloc = singleton();
	show_tiny_mem(alloc->data_tiny);
	show_small_mem(alloc->data_small);
	show_large_mem(alloc->data_large, alloc);
}
