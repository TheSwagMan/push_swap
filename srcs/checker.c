/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 16:58:11 by tpotier           #+#    #+#             */
/*   Updated: 2019/05/31 19:26:13 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int		check_op(char *o)
{
	return (ft_strequ("sa", o) || ft_strequ("sb", o) || ft_strequ("ss", o) \
			|| ft_strequ("pa", o) || ft_strequ("pb", o) \
			|| ft_strequ("ra", o) || ft_strequ("rb", o) || ft_strequ("rr", o) \
			|| ft_strequ("rra", o) || ft_strequ("rrb", o) \
			|| ft_strequ("rrr", o));
}

int		read_ops(t_ps_bench *bench)
{
	char	buff[4];
	int		n;
	char	t;

	while ((n = read(0, buff, 3)))
	{
		buff[3] = '\0';
		if (buff[2] == '\n')
			buff[2] = '\0';
		else
		{
			read(0, &t, 1);
			if (t != '\n')
				return (0);
		}
		if (!check_op(buff))
			return (0);
		ft_dlstadd_end(&bench->ops, ft_strdup(buff));
	}
	return (1);
}

void	disp_steps(t_ps_bench *bench, int opts)
{
	while (bench->ops && bench->ops->prev
			&& ft_strlen(bench->ops->prev->content) > 0)
		bench->ops = bench->ops->prev;
	if (bench->ops && !ft_strlen(bench->ops->content))
		bench->ops = bench->ops->next;
	disp_stack(bench, opts);
	while (bench->ops)
	{
		do_op(bench, bench->ops->content);
		disp_stack(bench, opts);
		bench->ops = bench->ops->next;
	}
}

int		main(int ac, char **av)
{
	t_ps_bench	bench;
	int			opts;
	int			*vals;
	int			size;
#ifdef GRAPHIC_MODE
	t_graph_env	env;
#endif

	if ((vals = parse_args(ac, av, &size, &opts))
			&& init_bench(vals, size, &bench)
			&& read_ops(&bench))
	{
		if (opts & OPT_G)
#ifdef GRAPHIC_MODE
			graph_loop(&env, &bench);
#else
			disp_steps(&bench, opts);
#endif
		do_ops(&bench);
		if (ft_sstkchkord(bench.sa) && !bench.sb->sp)
			ft_putstr("OK\n");
		else
			ft_putstr("KO\n");
	} else
		ft_putstr("Error\n");
	return (0);
}
