/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 16:58:02 by tpotier           #+#    #+#             */
/*   Updated: 2019/05/05 17:51:01 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_command(t_dlist *lst, char *cmd)
{
	ft_
}

void	sort(int *lst, int n)
{
	int	min;
	int	i;
	t_dlist	l;

	l = NULL;
	min = 0;
	i = 0;
	while (i < n - 1)
	{
		if (lst[i] > lst[i + 1])
		{
			ft_putendl("sa");
			lst[i] ^= lst[i + 1];
			lst[i + 1] ^= lst[i];
			lst[i] ^= lst[i + 1];
			while (i > 0)
			{
				ft_putendl("rra");
				i--;
			}
		} else
		{
			ft_putendl("ra");
			i++;
		}
	}
	while (i > 0)
	{
		ft_putendl("rra");
		i--;
	}
}

void	disp_tab(int *t, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		ft_putnbr(t[i++]);
		ft_putstr("\n");
	}
}

int		main(int ac, char **av)
{
	int	*tab;
	int	i;

	if (!check_args(ac, av))
		return (0);
	tab = malloc((ac - 1) * sizeof(int));
	i = 1;
	while (i < ac)
	{
		tab[i - 1] = atoi(av[i]);
		i++;
	}
	//disp_tab(tab, ac - 1);
	sort(tab, ac - 1);
	//disp_tab(tab, ac - 1);
	return (0);
}
