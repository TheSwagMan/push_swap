#include "push_swap.h"

void	disp_ops(t_dlist *ops)
{
	while (ops && ops->prev && ft_strlen(ops->prev->content) > 0)
		ops = ops->prev;
	if (ops && !ft_strlen(ops->content))
		ops = ops->next;
	while (ops)
	{
		ft_putendl(ops->content);
		ops = ops->next;
	}
}

void	do_ops(t_ps_bench *bench)
{
	while (bench->ops && bench->ops->prev
			&& ft_strlen(bench->ops->prev->content) > 0)
		bench->ops = bench->ops->prev;
	if (bench->ops && !ft_strlen(bench->ops->content))
		bench->ops = bench->ops->next;
	while (bench->ops)
	{
		do_op(bench, bench->ops->content);
		bench->ops = bench->ops->next;
	}
}

void	undo_op(t_ps_bench *bench, char *buff)
{
	if (ft_strequ("sa", buff) || ft_strequ("sb", buff) || ft_strequ("ss", buff))
		do_op(bench, buff);
	if (ft_strequ("ra", buff))
		do_op(bench, "rra");
	if (ft_strequ("rb", buff))
		do_op(bench, "rrb");
	if (ft_strequ("rr", buff))
		do_op(bench, "rrr");
	if (ft_strequ("rra", buff))
		do_op(bench, "ra");
	if (ft_strequ("rrb", buff))
		do_op(bench, "rb");
	if (ft_strequ("rrr", buff))
		do_op(bench, "rr");
	if (ft_strequ("pa", buff))
		do_op(bench, "pb");
	if (ft_strequ("pb", buff))
		do_op(bench, "pa");
}

int		do_op(t_ps_bench *bench, char *buff)
{
	if (ft_strequ("sa", buff) || ft_strequ("ss", buff))
		ft_sstkswap(bench->sa);
	else if (ft_strequ("sb", buff) || ft_strequ("ss", buff))
		ft_sstkswap(bench->sb);
	else if (ft_strequ("pa", buff))
	{
		if (bench->sb->sp)
			ft_sstkpush(bench->sa, ft_sstkpop(bench->sb));
	}
	else if (ft_strequ("pb", buff))
	{
		if (bench->sa->sp)
			ft_sstkpush(bench->sb, ft_sstkpop(bench->sa));
	}
	else if (ft_strequ("ra", buff) || ft_strequ("rr", buff))
		ft_sstkrot(bench->sa);
	else if (ft_strequ("rb", buff) || ft_strequ("rr", buff))
		ft_sstkrot(bench->sb);
	else if (ft_strequ("rra", buff) || ft_strequ("rrr", buff))
		ft_sstkrrot(bench->sa);
	else if (ft_strequ("rrb", buff) || ft_strequ("rrr", buff))
		ft_sstkrrot(bench->sb);
	else if (*buff)
		return (0);
	return (1);
}
