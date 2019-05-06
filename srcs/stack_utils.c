/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 21:48:44 by tpotier           #+#    #+#             */
/*   Updated: 2019/05/06 02:54:05 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		do_op(char *buff, t_sstack *sa, t_sstack *sb)
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
		return (0);
	return (1);
}

int		fill_stack(int *vals, int size, t_sstack **sa, t_sstack **sb)
{
	if (!(*sa = ft_sstkinit(size)) || !(*sb = ft_sstkinit(size)))
		return (0);
	while (size-- > 0)
		ft_sstkpush(*sa, vals[size]);
	free(vals);
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
