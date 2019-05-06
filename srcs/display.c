/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 02:46:12 by tpotier           #+#    #+#             */
/*   Updated: 2019/05/06 03:41:56 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	disp_n(int n)
{
	size_t			nw;

	nw = ft_nlen_base(n, 10);
	ft_putnchar(' ', (G_THK - nw) / 2 + ((G_THK - nw) % 2));
	ft_printf("%k%d%K", K_CYAN, n);
	ft_putnchar(' ', (G_THK - nw) / 2);
}

void	disp_cyl(int n, int max, int min)
{
	t_inter	in;
	t_inter	out;
	int		nw;

	out.l = 1;
	out.r = G_THK;
	in.l = min;
	in.r = max;
	nw = ft_map(n, in, out);
	ft_putnchar(' ', (G_THK - nw) / 2 + ((G_THK - nw) % 2));
	ft_printf("%k", K_GFG << K_BG_SHIFT);
	ft_printf("%*c", nw, ' ');
	ft_printf("%k", K_GBG << K_BG_SHIFT);
	ft_putnchar(' ', (G_THK - nw) / 2);
	ft_printf("%K");
}

void	disp_norm(t_sstack *sa, t_sstack *sb)
{
	size_t			i;

	i = sa->size;
	while (i-- > 0)
	{
		if (i < sa->sp)
			disp_n(sa->stack[i]);
		else
			ft_putnchar(' ', G_THK);
		ft_putnchar(' ', 2);
		if (i < sb->sp)
			disp_n(sb->stack[i]);
		else
			ft_putnchar(' ', G_THK);
		ft_putchar('\n');
	}
}

void	disp_graph(t_sstack *sa, t_sstack *sb)
{
	size_t			i;
	size_t			min_n;
	int				max_n;

	i = -1;
	min_n = sa->stack[0];
	max_n = sa->stack[0];
	while (++i < sa->size)
	{
		max_n = ft_max(ft_max(sa->stack[i], sb->stack[i]), max_n);
		min_n = ft_min(ft_min(sa->stack[i], sb->stack[i]), min_n);
	}
	while (i-- > 0)
	{
		ft_printf("%k", K_GBG << K_BG_SHIFT);
		if (i < sa->sp)
			disp_cyl(sa->stack[i], max_n, min_n);
		else
			ft_putnchar(' ', G_THK);
		ft_printf("%K");
		ft_putnchar(' ', 2);
		ft_printf("%k", K_GBG << K_BG_SHIFT);
		if (i < sb->sp)
			disp_cyl(sb->stack[i], max_n, min_n);
		else
			ft_putnchar(' ', G_THK);
		ft_printf("%K");
		ft_putchar('\n');
	}
}

void	disp_stack(t_sstack *sa, t_sstack *sb, char *op, int opts)
{
	int	nw;

	if (opts & OPT_O && op)
	{
		nw = ft_strlen(op);
		ft_printf("%k", K_NBG << K_BG_SHIFT | K_NFG | K_M_BOLD);
		ft_putnchar(' ', (G_THK * 2 + 2 - nw) / 2 + ((G_THK * 2 + 2 - nw) % 2));
		ft_putstr(op);
		ft_putnchar(' ', (G_THK * 2 + 2- nw) / 2);
		ft_printf("%K\n");
	}
	if (opts & OPT_G)
		disp_graph(sa, sb);
	else
		disp_norm(sa, sb);
	ft_printf("%k", K_NBG << K_BG_SHIFT | K_NFG | K_M_BOLD);
	ft_putnchar(' ', (G_THK - 1) / 2 + ((G_THK - 1) % 2));
	ft_putchar('A');
	ft_putnchar(' ', (G_THK - 1) / 2 + (G_THK - 1) / 2
			+ ((G_THK - 1) % 2) + 2);
	ft_putchar('B');
	ft_putnchar(' ', (G_THK - 1) / 2);
	ft_printf("%K\n");
}
