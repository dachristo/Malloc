/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 22:24:13 by dchristo          #+#    #+#             */
/*   Updated: 2017/05/19 16:34:41 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#define FT_HEX "ABCDEF"

t_alloc		*singleton(void)
{
	static t_alloc alloc;

	return (&alloc);
}

t_region_d	*new_data(t_region_d *data, size_t len, size_t region)
{
	void *p;

	p = mmap(0, region, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (p == (void *)-1)
		return (NULL);
	data = p;
	data->data = p + sizeof(t_region_d);
	data->len = len;
	data->isfree = 0;
	data->next = NULL;
	data->prev = NULL;
	return (data);
}

t_region_d	*new_data_in_if(t_region_d *data, size_t len, t_alloc *alloc,
							int region)
{
	void *p;

	p = data;
	data->next = p + sizeof(t_region_d) + data->len;
	data->next->len = len;
	data->next->data = p + 2 * sizeof(t_region_d) + data->len;
	data->next->isfree = 0;
	data->next->prev = p;
	data->next->next = NULL;
	if (region == 0)
		alloc->size_t_used += data->next->len + sizeof(t_region_d);
	else if (region == 1)
		alloc->size_s_used += data->next->len + sizeof(t_region_d);
	return (data->next);
}

t_region_d	*new_data_in_else(t_region_d *data, size_t len, t_alloc *alloc,
								int region)
{
	void *p;
	void *ptr;

	data->isfree = 0;
	if (data->len > len + sizeof(t_region_d))
	{
		p = data->next;
		ptr = data->next->next;
		data->next = p - data->len + len;
		data->next->isfree = 1;
		data->next->len = data->len - len - sizeof(t_region_d);
		data->next->data = data->next + 1;
		data->next->prev = data;
		data->next->next = p;
		data->len = len;
		data->next->next->next = ptr;
		data->next->next->prev = data->next;
	}
	else
	{
		data->len_left = data->len - len;
		data->len = len;
	}
	if (region == 0)
		alloc->size_t_used += data->next->len + sizeof(t_region_d);
	else if (region == 1)
		alloc->size_s_used += data->next->len + sizeof(t_region_d);
	return (data);
}

t_region_d	*new_data_in(t_region_d *data, size_t len, t_alloc *alloc,
						int region)
{
	while (data->next != NULL)
	{
		if (data->isfree == 1 && data->len <= len)
			break;
		data = data->next;
	}
	if (data->next == NULL || data->isfree == 0)
		return (new_data_in_if(data, len, alloc, region));
	else
		return (new_data_in_else(data, len, alloc, region));
}

void		ft_putdata(t_region_d *data)
{
	ft_puthex((size_t)data->data);
	ft_putstr("-");
	ft_puthex((size_t)(data->data + data->len));
	ft_putstr(" : ");
	ft_putnbr(data->len);
	ft_putstr(" octects ");
	ft_putnbr(data->isfree);
	ft_putstr(" : ");
	ft_putnbr(data->len_left);
	ft_putstr("\n");
}


void		show_tiny_mem(t_region_d *data, t_alloc *alloc)
{
	ft_putstr("TINY : ");
	ft_puthex((size_t)data);
	ft_putstr("\n");
	while (data != NULL)
	{
		if (data->isfree != 2)
			ft_putdata(data);
		data = data->next;
	}
	ft_putnbr(TINY * alloc->total_t_used + alloc->size_t_used);
	ft_putstr(" total octects used on ");
	ft_putnbr(TINY + TINY * alloc->total_t_used);
	ft_putstr("\n");
}

void		show_small_mem(t_region_d *data, t_alloc *alloc)
{
	ft_putstr("SMALL : ");
	ft_puthex((size_t)data);
	ft_putstr("\n");
	while (data != NULL)
	{
		if (data->isfree != 2)
			ft_putdata(data);
		data = data->next;
	}
	ft_putnbr(SMALL * alloc->total_s_used + alloc->size_s_used);
	ft_putstr(" total octects used on ");
	ft_putnbr(SMALL + SMALL * alloc->total_s_used);
	ft_putstr("\n");
}

void		show_large_mem(t_region_d *data, t_alloc *alloc)
{
	ft_putstr("LARGE : ");
	ft_puthex((size_t)data);
	ft_putstr("\n");
	while (data != NULL)
	{
		ft_putdata(data);
		data = data->next;
	}
	ft_putnbr(alloc->size_l_used);
	ft_putstr(" total octects used\n");
}

void		show_alloc_mem(void)
{
	t_alloc		*alloc;

	alloc = singleton();
	show_tiny_mem(alloc->data_tiny, alloc);
	show_small_mem(alloc->data_small, alloc);
	show_large_mem(alloc->data_large, alloc);
}

void	ft_bzero(void *s, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = '\0';
		i++;
	}
}

void	*ft_memcpy(void *str1, const void *str2, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		((char *)str1)[i] = ((char *)str2)[i];
		i++;
	}
	return (str1);
}

int		ft_strlen(char *str)
{
	int i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

void	ft_puthex(size_t n)
{
	char	c;

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

void	ft_putchar(char c)
{
	write(1, &c, 1);
}


void	ft_putnbr(long n)
{
	if (n < 0)
	{
		ft_putchar('-');
		n *= -1;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putchar(n % 10 + '0');
	}
	else if (n < 10)
	{
		ft_putchar(n + '0');
	}
}
