/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 16:59:06 by tpotier           #+#    #+#             */
/*   Updated: 2019/05/29 13:11:14 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "libft.h"

# define OPT_C	(1 << 1)
# define OPT_V	(1 << 2)
# define OPT_O	(1 << 3)
# define OPT_G	(1 << 4)

# define G_THK	70

# define K_GBG	0x256E91l
# define K_GFG	0xFFA237l
# define K_NBG	0x043F5Bl
# define K_NFG	0xFFE433l
# define K_OFG	0x97566Cl

typedef enum	e_op
{
	OP_RR = 0,
	OP_R
}				t_op;

typedef struct	s_ps_bench
{
	t_dlist		*ops;
	t_sstack	*sa;
	t_sstack	*sb;
}				t_ps_bench;

typedef struct	s_dist
{
	size_t		count;
	t_op		op;
}				t_dist;

int		*parse_args(int ac, char **av, int *size, int *opts);
void	disp_stack(t_sstack *sa, t_sstack *sb, char *op, int opts);
int		do_op(t_ps_bench *bench, char *buff);
int		init_bench(int *vals, int size, t_ps_bench *bench);
void	free_charpp(char **c);

void	bench_step_forward(t_ps_bench *bench);
void	bench_step_backward(t_ps_bench *bench);

#endif
