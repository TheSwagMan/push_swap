/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 16:58:11 by tpotier           #+#    #+#             */
/*   Updated: 2019/05/06 01:18:40 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		do_ops(t_sstack *sa, t_sstack *sb, int opts)
{
	char	*buff;

	if (opts & OPT_C)
		disp_stack(sa, sb, NULL, opts);
	while (ft_getnextline(0, &buff) > 0)
	{
		if (!do_op(buff, sa, sb))
			return (0);
		if (opts & OPT_C)
			disp_stack(sa, sb, buff, opts);
		free(buff);
	}
	return (1);
}

int		main(int ac, char **av)
{
	t_sstack	*sa;
	t_sstack	*sb;
	int			opts;
	int			*vals;
	int			size;

	sa = NULL;
	sb = NULL;
	if ((vals = parse_args(ac, av, &size, &opts))
			&& fill_stack(vals, size, &sa, &sb) && do_ops(sa, sb, opts))
	{
		if (ft_sstkchkord(sa))
			ft_putstr("OK\n");
		else
			ft_putstr("KO\n");
	} else
		ft_putstr("Error\n");
	return (0);
}
