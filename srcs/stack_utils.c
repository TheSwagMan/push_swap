/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 21:48:44 by tpotier           #+#    #+#             */
/*   Updated: 2019/05/21 07:31:24 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

void	free_charpp(char **c)
{
	int	i;

	i = 0;
	while (c[i])
		free(c[i++]);
	free(c);
}
