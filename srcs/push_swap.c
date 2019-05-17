/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 16:58:02 by tpotier           #+#    #+#             */
/*   Updated: 2019/05/17 17:38:12 by tpotier          ###   ########.fr       */
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

void	push_ops(t_dlist **ops, char *op)
{
	while (*ops && (*ops)->next)
		*ops = (*ops)->next;
	//ft_putstr("Action:");
	//ft_putendl(op);
#if 0
	if (*ops && ((ft_strequ(op, "ra") && ft_strequ((*ops)->content, "rra"))
			|| (ft_strequ(op, "rra") && ft_strequ((*ops)->content, "ra"))
			|| (ft_strequ(op, "rrb") && ft_strequ((*ops)->content, "rb"))
			|| (ft_strequ(op, "rb") && ft_strequ((*ops)->content, "rrb"))
			|| (ft_strequ(op, "sa") && ft_strequ((*ops)->content, "sa"))
			|| (ft_strequ(op, "sb") && ft_strequ((*ops)->content, "sb"))
			|| (ft_strequ(op, "pa") && ft_strequ((*ops)->content, "pb"))
			|| (ft_strequ(op, "pb") && ft_strequ((*ops)->content, "pa"))))
		ft_dlstdel(ops, NULL);
	else if (*ops && ((ft_strequ(op, "sa") && ft_strequ((*ops)->content, "sb"))
			|| (ft_strequ(op, "sb") && ft_strequ((*ops)->content, "sa"))))
	{
		ft_dlstdel(ops, NULL);
		ft_dlstadd_end(ops, "ss");
	}
	else if (*ops && ((ft_strequ(op, "ra") && ft_strequ((*ops)->content, "rb"))
			|| (ft_strequ(op, "rb") && ft_strequ((*ops)->content, "ra"))))
	{
		ft_dlstdel(ops, NULL);
		ft_dlstadd_end(ops, "rr");
	}
	else if (*ops && ((ft_strequ(op, "rra") && ft_strequ((*ops)->content, "rrb"))
			|| (ft_strequ(op, "rrb") && ft_strequ((*ops)->content, "rra"))))
	{
		ft_dlstdel(ops, NULL);
		ft_dlstadd_end(ops, "rrr");
	}
	else
#endif
		ft_dlstadd_end(ops, op);
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

int		do_rop(t_dlist **ops, char *op, t_sstack *sa, t_sstack *sb)
{
	if (!do_op(op, sa, sb))
		return (0);
	push_ops(ops, op);
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

size_t		get_loc(t_sstack *sa, int n)
{
	size_t	i;

	i = 0;
	while (i < sa->sp && sa->stack[i] > n)
		i++;
	return (i);
}

void	sort_3(t_dlist **ops, int *vals, int size)
{
	t_sstack	*sa;
	t_sstack	*sb;
	int			med;
	size_t		old_sz;

	sa = NULL;
	sb = NULL;
	if (!fill_stack(vals, size, &sa, &sb))
		return ;
	while (sa->sp > 3)
	{
		med = get_median(sa->stack, sa->sp);
		old_sz = sa->sp;
		ft_putendl_fd("ok", 2);
		while (sa->sp > old_sz / 2)
		{
			ft_putnbr_fd(sa->sp, 2);
			ft_putstr_fd(" - ", 2);
			ft_putnbr_fd(old_sz / 2, 2);
			ft_putstr_fd(" - ", 2);
			ft_putnbr_fd(med, 2);
			ft_putchar_fd('\n', 2);
			if (sa->stack[sa->sp - 1] <= med)
				do_rop(ops, "pb", sa, sb);
			else
				do_rop(ops, "ra", sa, sb);
		}
	}

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


int		main(int ac, char **av)
{
	int		*vals;
	int		size;
	int		opts;
	t_dlist	*ops;

	ops = NULL;
	if ((vals = parse_args(ac, av, &size, &opts)))
	{
		//disp_tab(tab, size);
		//quicksort(&ops, tab, size);
		//disp_tab(tab, size);
		//sort(&ops, vals, size);
		sort_3(&ops, vals, size);
		disp_ops(ops);
	}
	return (0);
}
