/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 16:09:07 by tpotier           #+#    #+#             */
/*   Updated: 2019/05/05 16:10:47 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		check_args(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 2)
		return (0);
	while (--ac >= 1)
	{
		i = 0;
		while (av[ac][i])
		{
			if (!ft_isdigit(av[ac][i]) && av[ac][0] != '-')
				return (0);
			i++;
		}
	}
	return (1);
}
