/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 16:58:11 by tpotier           #+#    #+#             */
/*   Updated: 2019/05/02 20:21:02 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		do_ops(t_sstack *sa, t_sstack *sb)
{
	char	*buff;

	while (ft_getnextline(0, &buff) > 0)
	{
		if (ft_strequ("sa", buff) || ft_strequ("ss", buff))
			ft_sstkswap(sa);
		else if (ft_strequ("sb", buff) || ft_strequ("ss", buff))
			ft_sstkswap(sb);
		else if (ft_strequ("pa", buff))
		{
			if (sb->sp)
				ft_sstkpush(sa, ft_sstkpop(sb));
		}
		else if (ft_strequ("pb", buff))
		{
			if (sa->sp)
				ft_sstkpush(sb, ft_sstkpop(sa));
		}
		else if (ft_strequ("ra", buff) || ft_strequ("rr", buff))
			ft_sstkrot(sa);
		else if (ft_strequ("rb", buff) || ft_strequ("rr", buff))
			ft_sstkrot(sb);
		else if (ft_strequ("rra", buff) || ft_strequ("rrr", buff))
			ft_sstkrrot(sa);
		else if (ft_strequ("rrb", buff) || ft_strequ("rrr", buff))
			ft_sstkrrot(sb);
		else if (*buff)
		{
			ft_putendl(buff);
			return (0);
		}
		ft_putstr("Stack a:\n");
		ft_sstkdisp(sa);
		ft_putstr("Stack b:\n");
		ft_sstkdisp(sb);
		free(buff);
	}
	return (1);
}

void	fill_stack(int ac, char **av, t_sstack *sa)
{
	while (--ac > 0)
		ft_sstkpush(sa, ft_atoi(av[ac]));
}

int		check_args(int ac, char **av)
{
	(void)av;
	if (ac < 2)
		return (0);
	while (ac > 1)
	{
		ac--;
	}
	return (1);
}

int		main(int ac, char **av)
{
	t_sstack *sa;
	t_sstack *sb;

	if (!check_args(ac, av) || !(sa = ft_sstkinit(ac - 1)) || !(sb = ft_sstkinit(ac - 1)))
		ft_putstr("Error\n");
	else
	{
		fill_stack(ac, av, sa);
		do_ops(sa, sb);
		if (ft_sstkchkord(sa))
			ft_putstr("OK\n");
		else
			ft_putstr("KO\n");
	}
	return (0);
}
