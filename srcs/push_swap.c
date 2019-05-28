/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 16:58:02 by tpotier           #+#    #+#             */
/*   Updated: 2019/05/28 22:55:19 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	disp_ops(t_dlist *ops)
{
	while (ops && ops->prev)
		ops = ops->prev;
	while (ops)
	{
		ft_putendl(ops->content);
		ops = ops->next;
	}
}

void	push_ops(t_ps_bench *bench, char *op)
{
	while (bench->ops && bench->ops->next)
		bench->ops = bench->ops->next;
	//ft_putstr("Action:");
	//ft_putendl(op);
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
	else if (bench->ops && ((ft_strequ(op, "ra") && ft_strequ(bench->ops->content, "rb"))
			|| (ft_strequ(op, "rb") && ft_strequ(bench->ops->content, "ra"))))
	{
		ft_dlstdel(&(bench->ops), NULL);
		ft_dlstadd_end(&(bench->ops), "rr");
	}
	else if (bench->ops && ((ft_strequ(op, "rra") && ft_strequ(bench->ops->content, "rrb"))
			|| (ft_strequ(op, "rrb") && ft_strequ(bench->ops->content, "rra"))))
	{
		ft_dlstdel(&(bench->ops), NULL);
		ft_dlstadd_end(&(bench->ops), "rrr");
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

int		get_median(int *vals, size_t size)
{
	int		*new;
	int		min;
	size_t	i;
	int		sorted;

	if (!(new = (int *)malloc(size * sizeof(int))))
		return (0);
	ft_memcpy(new, vals, size * sizeof(int));
	min = 0;
	sorted = 0;
	while (!sorted)
	{
		i = 0;
		sorted = 1;
		while (i < size - 1)
		{
			if (new[i] > new[i + 1])
			{
				ft_swap(&(new[i]), &(new[i + 1]), sizeof(*new));
				sorted = 0;
			}
			i++;
		}
	}
	min = new[size / 2 - (size % 2 ? 0 : 1)];
	free(new);
	return (min);
}

size_t		_sortstack(t_ps_bench *ben, size_t low)
{
	size_t		i;
	size_t		osp;
	size_t		ret;
	int			med;

	i = 0;
	osp = (ben->sa->sp - low) / 2;
	ret = ben->sa->sp - osp;
	med = get_median((&ben->sa->stack[low]), ben->sa->sp - low);
	/*ft_printf("med: %zu, low: %zu, a->sp - 1: %zu\n", a->med, low, a->sp - 1);*/
	while (ben->sa->sp - low > osp)
		if (ben->sa->stack[ben->sa->sp - 1] <= med)
			do_rop(ben, "pb");
		else
		{
			i++;
			do_rop(ben, "ra");
		}
	while (i-- > 0)
		do_rop(ben, "rra");
	return (ret);
}

void	_quicksort(t_ps_bench *ben, size_t low)
{
	size_t		osp;

	if (low < ben->sa->sp - 1)
	{
		osp = _sortstack(ben, low);
		/*ft_printf("low: %zu, a->sp: %zu, osp: %zu\nstack a: ", low, a->sp, osp);*/
		/*print_stack(a);*/
		/*ft_printf("\nstack b:");*/
		/*print_stack(b);*/
		/*ft_putchar('\n');*/
		_quicksort(ben, low);
		low = ben->sa->sp;
		if (osp <= 2 && ben->sb->sp > 1)
		{
			if (ben->sb->stack[ben->sb->sp - 1] < ben->sb->stack[ben->sb->sp - 2])
				do_rop(ben, "sb");
			do_rop(ben, "pa");
			do_rop(ben, "pa");
			low += osp;
		}
		else
			while (osp-- > 0 && ben->sb->sp)
				do_rop(ben, "pa");
		_quicksort(ben, low);
	}
}

void	smart_rotate_b(t_ps_bench *ben, size_t k)
{
	size_t	n;

	n = 0;
	if (k > ben->sb->sp / 2)
	{
		while (n++ < ben->sb->sp - k)
			do_rop(ben, "rrb");
	}
	else
		while (n++ < k)
			do_rop(ben, "rb");
}

void	_insertion_sort(t_ps_bench *ben)
{
	size_t	i;
	int		min;
	int		max;
	int		omin;

	min = ben->sa->stack[ben->sa->sp - 1];
	max = min;
	do_rop(ben, "pb");
	while (ben->sa->sp)
	{
		if (ben->sa->stack[ben->sa->sp - 1] > max \
				|| ben->sa->stack[ben->sa->sp - 1] < min)
		{
			/*while (ben->sb->stack[ben->sb->sp - 1] < ben->sb->stack[0])*/
				/*do_rop(ben, "rb");*/
			if (ben->sb->sp > 1)
			{
				i = 0;
				while (i < ben->sb->sp - 2 && ben->sb->stack[i] < ben->sb->stack[i + 1])
					i++;
				if (i)
					smart_rotate_b(ben, ben->sb->sp - i - 1);
			}
			omin = min;
			min = ft_min(ben->sa->stack[ben->sa->sp - 1], min);
			max = ft_max(ben->sa->stack[ben->sa->sp - 1], max);
			do_rop(ben, "pb");
			if (ben->sa->stack[ben->sa->sp - 1] < omin)
				do_rop(ben, "rb");
		}
		else
		{
			while (ben->sb->stack[ben->sb->sp - 1] < ben->sa->stack[ben->sa->sp - 1])
				do_rop(ben, "rrb");
			while (ben->sb->stack[ben->sb->sp - 1] > ben->sa->stack[ben->sa->sp - 1])
				do_rop(ben, "rb");
			min = ft_min(ben->sa->stack[ben->sa->sp - 1], min);
			max = ft_max(ben->sa->stack[ben->sa->sp - 1], max);
			do_rop(ben, "pb");
		}
	}
	i = 0;
	while (i < ben->sb->sp - 2 && ben->sb->stack[i] < ben->sb->stack[i + 1])
		i++;
	smart_rotate_b(ben, ben->sb->sp - i - 1);
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

void	optimize_ops(t_dlist *ops, int size)
{
	int		ra_count;
	int		rra_count;
	t_dlist	*tmp;

	while (ops && ops->prev)
		ops = ops->prev;
	ra_count = 0;
	rra_count = 0;
	while (ops)
	{
		if (ft_strequ(ops->content, "ra"))
			ra_count++;
		else
		{
			if (ra_count > size / 2)
				ops = 0;
			tmp = ops;
			ra_count = 0;
		}
		if (ft_strequ(ops->content, "rra"))
			rra_count++;
		else
		{
			if (rra_count > size / 2)
				ops = 0;
			tmp = ops;
			rra_count = 0;
		}
		ops = ops->next;
	}
}

/*
void	sort(t_dlist **ops, int *lst, int n)
{
	int	min;
	int	i;

	min = 0;
	i = 0;
	while (i < n - 1)
	{
		if (lst[i] > lst[i + 1])
		{
			push_ops(ops, "sa");
			ft_swap(&(lst[i]), &(lst[i + 1]), sizeof(*lst));
			while (i-- > 0)
				push_ops(ops, "rra");
			i = 0;
		} else
		{
			push_ops(ops, "ra");
			i++;
		}
	}
	while (i-- > 0)
		push_ops(ops, "rra");
}
*/


size_t		get_loc(t_sstack *sa, int n)
{
	size_t	i;

	i = 0;
	while (i < sa->sp && sa->stack[i] > n)
		i++;
	return (i);
}

int		quickpart_stk(t_ps_bench *bench)
{
	int		piv;
	size_t	old_sz;

	if (bench->sa->sp > 2)
	{
		piv = get_median(bench->sa->stack, bench->sa->sp);
		old_sz = bench->sa->sp;
		while (bench->sa->sp > old_sz / 2)
		{
			if (bench->sa->stack[bench->sa->sp - 1] <= piv)
				do_rop(bench, "pb");
			else
				do_rop(bench, "ra");
		}
		return (old_sz / 2);
	}
	return (2);
}

void	quicksort_stk(t_ps_bench *bench)
{
	(void)bench;
}


void	quicksort_stk_wrp(t_ps_bench *bench)
{
	quicksort_stk(bench);
}

/*
void	split_and_sort(t_dlist **ops, t_sstack *sa, t_sstack *sb)
{
	int			med;
	size_t		old_sz;
	size_t		count;

	count = 0;
	if (sa->sp > 2)
	{
		med = get_median(sa->stack, sa->sp);
		old_sz = sa->sp;
		count = sa->sp - old_sz / 2;
		while (sa->sp > old_sz / 2)
		{
			if (sa->stack[sa->sp - 1] <= med)
				do_rop(ops, "pb", sa, sb);
			else
				do_rop(ops, "ra", sa, sb);
		}
		split_and_sort(ops, sa, sb);
	}
	if (sa->stack[sa->sp - 1] > sa->stack[sa->sp - 2])
		do_rop(ops, "sa", sa, sb);
	while (count--)
		do_rop(ops, "pa", sa, sb);
}

void	sort_3(t_dlist **ops, int *vals, int size)
{
	t_sstack	*sa;
	t_sstack	*sb;

	sa = NULL;
	sb = NULL;
	if (!fill_stack(vals, size, &sa, &sb))
		return ;
	split_and_sort(ops, sa, sb);
}

int		sort2(t_dlist **ops, int *vals, int size)
{
	t_sstack	*sa;
	t_sstack	*sb;
	size_t		n;
	size_t		i;
	size_t		k;

	sa = NULL;
	sb = NULL;
	if (!fill_stack(vals, size, &sa, &sb))
		return (0);
	i = 1;
	while (i * i < sa->size)
	{
		if (i % 2)
		{
			n = 0;
			while (sa->sp > i * i)
			{
				k = 0;
				while (k++ < i)
					do_rop(ops, "pb", sa, sb);
				while (k--)
				{
					if (sb->stack[sb->sp - 1] > sa->stack[sa->sp - 1] && n % 2)
				{
						do_rop(ops, "pb", sa, sb);
						do_rop(ops, "rb", sa, sb);
					}
					else
					{
						do_rop(ops, "rb", sa, sb);
						do_rop(ops, "pb", sa, sb);
					}
					do_rop(ops, "rb", sa, sb);
				}
				n++;
			}
		}
		else
		{
			while (sb->sp > i * i)
			{
				k = 0;
				while (k++ < i)
					do_rop(ops, "pa", sa, sb);
				while (k--)
				{
					if (sb->stack[sb->sp - 1] > sa->stack[sa->sp - 1])
					{
						do_rop(ops, "pa", sa, sb);
						do_rop(ops, "ra", sa, sb);
					}
					else
					{
						do_rop(ops, "ra", sa, sb);
						do_rop(ops, "pa", sa, sb);
					}
				}
			}
		}
		if (i == 2)
			return (1);
		i++;
	}
	while (sa->sp)
	{
		do_rop(ops, "pb", sa, sb);
		if (sa->sp)
			do_rop(ops, "pb", sa, sb);
		if (sa->sp > 1 && sa->stack[sa->sp - 1] > sa->stack[sa->sp - 2])
			do_rop(ops, "sa", sa, sb);
		if (sb->sp > 1 && sb->stack[sb->sp - 1] < sb->stack[sb->sp - 2])
			do_rop(ops, "sb", sa, sb);
		if (sa->sp > 1)
		{
			do_rop(ops, "pb", sa, sb);
			do_rop(ops, "pb", sa, sb);
		}
	}
	while (sb->sp)
	{
		do_rop(ops, "pa", sa, sb);
		if (sb->sp > 1 && sb->stack[sb->sp - 1] < sb->stack[sb->sp - 2])
			do_rop(ops, "sb", sa, sb);
		do_rop(ops, "pa", sa, sb);
		if (sa->sp > 1 && sa->stack[sa->sp - 1] > sa->stack[sa->sp - 2])
			do_rop(ops, "sa", sa, sb);
		if (sb->sp > 1 && sb->stack[sb->sp - 1] < sb->stack[sb->sp - 2])
			do_rop(ops, "sb", sa, sb);
		if (sb->sp)
			do_rop(ops, "pa", sa, sb);
		if (sa->sp > 1 && sa->stack[sa->sp - 1] > sa->stack[sa->sp - 2])
			do_rop(ops, "sa", sa, sb);
		if (sb->sp)
			do_rop(ops, "pa", sa, sb);
	}
	return (0);
	while (sb->sp)
	{
		n = get_loc(sa, sb->stack[sb->sp - 1]);
		while (n--)
			do_rop(ops, "rra", sa, sb);
		do_rop(ops, "pa", sa, sb);
		while (sa->sp > 1 && sa->stack[sa->sp - 1] >= sa->stack[0])
			do_rop(ops, "ra", sa, sb);
	}
	while (sa->stack[0] <= sa->stack[sa->sp - 1])
		do_rop(ops, "ra", sa, sb);
	return (1);
}

void	quicksort_rec(t_dlist **ops, int *array, int low, int high)
{
	int	pivot_index = high;
	int	border = low;
	int	j;
	int	i;

	if (low < high)
	{
		j = low;
		while (j < high)
		{
			if (array[j] < array[pivot_index])
			{
				i = 0;
				while (i++ < border)
					push_ops(ops, "ra");
				push_ops(ops, "pb");
				while (i-- > 0)
					push_ops(ops, "rra");
				while (i++ < j - 1)
					push_ops(ops, "ra");
				push_ops(ops, "pb");
				push_ops(ops, "sb");
				push_ops(ops, "pa");
				while (i-- > 0)
					push_ops(ops, "rra");
				while (i++ < border)
					push_ops(ops, "ra");
				push_ops(ops, "pa");
				while (i-- > 1)
					push_ops(ops, "rra");
				ft_swap(&(array[border++]), &(array[j]), sizeof(int));
			}
			j++;
		}
		i = 0;
		while (i++ < border)
			push_ops(ops, "ra");
		push_ops(ops, "pb");
		while (i-- > 0)
			push_ops(ops, "rra");
		while (i++ < high - 1)
			push_ops(ops, "ra");
		push_ops(ops, "pb");
		push_ops(ops, "sb");
		push_ops(ops, "pa");
		while (i-- > 0)
			push_ops(ops, "rra");
		while (i++ < border)
			push_ops(ops, "ra");
		push_ops(ops, "pa");
		while (i-- > 1)
			push_ops(ops, "rra");
		ft_swap(&(array[border]), &(array[high]), sizeof(int));
		quicksort_rec(ops, array, low, border - 1);
		quicksort_rec(ops, array, border + 1, high);
	}
}

void	quicksort(t_dlist **ops, int *array, int size)
{
	quicksort_rec(ops, array, 0, size - 1);
}
*/

int		main(int ac, char **av)
{
	int			*vals;
	int			size;
	int			opts;
	t_ps_bench	bench;

	if ((vals = parse_args(ac, av, &size, &opts))
			&& init_bench(vals, size, &bench))
	{
		//disp_tab(tab, size);
		//quicksort(&ops, tab, size);
		//disp_tab(tab, size);
		//sort(&ops, vals, size);
		//sort_3(&ops, vals, size);
		//quicksort_stk_wrp(&bench);
		_insertion_sort(&bench);
		disp_ops(bench.ops);
	} else
		ft_putendl("Damn son !");
	return (0);
}
