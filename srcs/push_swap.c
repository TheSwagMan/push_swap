/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 16:58:02 by tpotier           #+#    #+#             */
/*   Updated: 2019/08/19 16:24:28 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_ops(t_ps_bench *bench, char *op)
{
	while (bench->ops && bench->ops->next)
		bench->ops = bench->ops->next;
#if 1
	if (bench->ops && ((ft_strequ(op, "ra") && ft_strequ(bench->ops->content, "rra"))
			|| (ft_strequ(op, "rra") && ft_strequ(bench->ops->content, "ra"))
			|| (ft_strequ(op, "rrb") && ft_strequ(bench->ops->content, "rb"))
			|| (ft_strequ(op, "rb") && ft_strequ(bench->ops->content, "rrb"))
			|| (ft_strequ(op, "sa") && ft_strequ(bench->ops->content, "sa"))
			|| (ft_strequ(op, "sb") && ft_strequ(bench->ops->content, "sb"))
			|| (ft_strequ(op, "pa") && ft_strequ(bench->ops->content, "pb"))
			|| (ft_strequ(op, "pb") && ft_strequ(bench->ops->content, "pa"))))
		ft_dlstdel(&(bench->ops), NULL);
	else if (bench->ops && ((ft_strequ(op, "sa") && ft_strequ(bench->ops->content, "sb"))
			|| (ft_strequ(op, "sb") && ft_strequ(bench->ops->content, "sa"))))
	{
		ft_dlstdel(&(bench->ops), NULL);
		ft_dlstadd_end(&(bench->ops), "ss");
	}
	else if (bench->ops && (ft_strequ(op, "ra") || ft_strequ(op, "rb")))
	{
		while (ft_strequ(bench->ops->content, "rr"))
			bench->ops = bench->ops->prev;
		if ((ft_strequ(op, "ra") && ft_strequ(bench->ops->content, "rb"))
			|| (ft_strequ(op, "rb") && ft_strequ(bench->ops->content, "ra")))
			bench->ops->content = "rr";
		else
			ft_dlstadd_end(&(bench->ops), op);
	}
	else if (bench->ops && (ft_strequ(op, "rra") || ft_strequ(op, "rrb")))
	{
		while (ft_strequ(bench->ops->content, "rrr"))
			bench->ops = bench->ops->prev;
		if ((ft_strequ(op, "rra") && ft_strequ(bench->ops->content, "rrb"))
			|| (ft_strequ(op, "rrb") && ft_strequ(bench->ops->content, "rra")))
			bench->ops->content = "rrr";
		else
			ft_dlstadd_end(&(bench->ops), op);
	}
	else
#endif
		ft_dlstadd_end(&(bench->ops), op);
}

int		do_rop(t_ps_bench *bench, char *op)
{
	if (!do_op(bench, op))
		return (0);
	push_ops(bench, op);
	return (1);
}

t_dist	*init_dist(size_t count, int op)
{
	t_dist	*d;

	if (!(d = malloc(sizeof(*d))))
		return (NULL);
	d->count = count;
	d->op = op;
	return (d);
}

t_dist	rotation_count(int n, t_sstack *s)
{
	t_sstack	*sc;
	t_dist		d;

	d.count = 0;
	d.op = OP_R;
	sc = ft_sstkcpy(s);
	while (sc->sp > 1 && (n < sc->stack[sc->sp - 1] || n > sc->stack[0]) \
			&& !(sc->stack[0] < sc->stack[sc->sp - 1] \
				&& (n > sc->stack[sc->sp - 1] || n < sc->stack[0])))
	{
		ft_sstkrot(sc);
		d.count++;
	}
	ft_sstkdel(&sc);
	if (d.count > s->sp / 2)
	{
		d.count = s->sp - d.count;
		d.op = OP_RR;
	}
	return (d);
}

void	insertion_sort(t_ps_bench *ben)
{
	size_t	n;
	t_dist	best_score;
	size_t	best_index;
	t_dist	t;

	do_rop(ben, "pb");
	while (ben->sa->sp)
	{
		n = 0;
		best_score = rotation_count(ben->sa->stack[ben->sa->sp - 1], ben->sb);
		best_index = 0;
		while (++n < best_score.count && n < ben->sa->sp)
		{
			t = rotation_count(ben->sa->stack[ben->sa->sp - 1 - n], ben->sb);
			if (t.count < best_score.count + n)
			{
				best_index = n;
				best_score = t;
			}
		}
		while (best_index--)
			do_rop(ben, "ra");
		while (best_score.count--)
			do_rop(ben, best_score.op == OP_R ? "rb" : "rrb");
		do_rop(ben, "pb");
	}
	n = 0;
	while (ben->sb->stack[ben->sb->sp - 1 - n] > ben->sb->stack[ben->sb->sp - n]
			|| n >= ben->sb->sp - 1)
		n++;
	if (n > ben->sb->sp / 2)
		while (n++ < ben->sb->sp)
			do_rop(ben, "rrb");
	else
		while (n--)
			do_rop(ben, "rb");
	while (ben->sb->sp)
		do_rop(ben, "pa");
}
void	disp_tab(int *t, int n)
{
	int	i;

	i = 0;
	ft_putendl("Array:");
	while (i < n)
	{
		ft_putnbr(t[i++]);
		ft_putstr("\n");
	}
}

int		main(int ac, char **av)
{
	int			*vals;
	int			size;
	int			opts;
	t_ps_bench	bench;

	if ((vals = parse_args(ac, av, &size, &opts))
			&& init_bench(vals, size, &bench))
	{
		insertion_sort(&bench);
		disp_ops(bench.ops);
	} else
		ft_putendl("Damn son !");
	return (0);
}
