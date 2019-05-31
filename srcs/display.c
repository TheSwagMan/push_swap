/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 02:46:12 by tpotier           #+#    #+#             */
/*   Updated: 2019/05/31 19:25:04 by tpotier          ###   ########.fr       */
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

void	disp_graph(t_ps_bench *ben)
{
	size_t			i;
	size_t			min_n;
	int				max_n;

	i = -1;
	min_n = ben->sa->stack[0];
	max_n = ben->sa->stack[0];
	while (++i < ben->sa->size)
	{
		max_n = ft_max(ft_max(ben->sa->stack[i], ben->sb->stack[i]), max_n);
		min_n = ft_min(ft_min(ben->sa->stack[i], ben->sb->stack[i]), min_n);
	}
	while (i-- > 0)
	{
		ft_printf("%k", K_GBG << K_BG_SHIFT);
		if (i < ben->sa->sp)
			disp_cyl(ben->sa->stack[i], max_n, min_n);
		else
			ft_putnchar(' ', G_THK);
		ft_printf("%K");
		ft_putnchar(' ', 2);
		ft_printf("%k", K_GBG << K_BG_SHIFT);
		if (i < ben->sb->sp)
			disp_cyl(ben->sb->stack[i], max_n, min_n);
		else
			ft_putnchar(' ', G_THK);
		ft_printf("%K");
		ft_putchar('\n');
	}
}

void	disp_stack(t_ps_bench *bench, int opts)
{
	int	nw;

	if (opts & OPT_O)
	{
		nw = ft_strlen(bench->ops->content);
		ft_printf("%k", K_NBG << K_BG_SHIFT | K_NFG | K_M_BOLD);
		ft_putnchar(' ', (G_THK * 2 + 2 - nw) / 2 + ((G_THK * 2 + 2 - nw) % 2));
		ft_putstr(bench->ops->content);
		ft_putnchar(' ', (G_THK * 2 + 2- nw) / 2);
		ft_printf("%K\n");
	}
	disp_graph(bench);
	ft_printf("%k", K_NBG << K_BG_SHIFT | K_NFG | K_M_BOLD);
	ft_putnchar(' ', (G_THK - 1) / 2 + ((G_THK - 1) % 2));
	ft_putchar('A');
	ft_putnchar(' ', (G_THK - 1) / 2 + (G_THK - 1) / 2
			+ ((G_THK - 1) % 2) + 2);
	ft_putchar('B');
	ft_putnchar(' ', (G_THK - 1) / 2);
	ft_printf("%K\n");
}
