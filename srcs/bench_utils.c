/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <tpotier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 04:33:55 by tpotier           #+#    #+#             */
/*   Updated: 2019/05/31 18:48:39 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		init_bench(int *vals, int size, t_ps_bench *bench)
{
	bench->ops = NULL;
	ft_dlstadd_end(&bench->ops, "");
	if (!(bench->sa = ft_sstkinit(size)))
		return (0);
	if (!(bench->sb = ft_sstkinit(size)))
	{
		free(bench->sa);
		return (0);
	}
	while (size-- > 0)
		ft_sstkpush(bench->sa, vals[size]);
	free(vals);
	return (1);
}

int		bench_step_forward(t_ps_bench *bench)
{
	if (bench->ops->next)
	{
		bench->ops = bench->ops->next;
		do_op(bench, bench->ops->content);
		return (1);
	}
	return (0);
}

int		bench_step_backward(t_ps_bench *bench)
{
	if (bench->ops->prev)
	{
		undo_op(bench, bench->ops->content);
		bench->ops = bench->ops->prev;
		return (1);
	}
	return (0);
}
