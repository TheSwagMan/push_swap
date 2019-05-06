/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 16:09:07 by tpotier           #+#    #+#             */
/*   Updated: 2019/05/06 02:59:49 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		parse_opt(char *c)
{
	int	o;

	o = 0;
	if (*c)
		o |= parse_opt(c + 1);
	if (*c == 'c')
		o |= OPT_C;
	if (*c == 'v')
		o |= OPT_V;
	if (*c == 'o')
		o |= OPT_O;
	if (*c == 'g')
		o |= OPT_G;
	return (o);
}

int		check_arg(char *arg)
{
	int		i;

	i = 0;
	if (arg[0] == '-' && !ft_isdigit(arg[1]))
		return (1);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]) && arg[i] != ' ' && !(arg[i] == '-' && i == 0))
			return (-1);
		i++;
	}
	return (0);
}

int		*parse_split(char *av, int *size)
{
	int		*res;
	char	**tmp;
	int		i;

	tmp = ft_strsplit(av, ' ');
	*size = 0;
	while (tmp[*size])
		if (check_arg(tmp[(*size)++]))
		{
			free_charpp(tmp);
			return (NULL);
		}
	if (!(res = malloc(*size * sizeof(*res))))
		return (NULL);
	i = -1;
	while (++i < *size)
	{
		res[i] = atoi(tmp[i]);
		free(tmp[i]);
	}
	free(tmp);
	return (res);
}

int		*parse_all(int ac, char **av, int *size)
{
	int	*res;
	int	i;
	int	t;

	*size = 0;
	i = 0;
	while (++i < ac)
		if (!(t = check_arg(av[i])))
			(*size)++;
		else if (t == -1)
			return (NULL);
	if (!*size)
		return (NULL);
	if (!(res = malloc(*size * sizeof(*res))))
		return (NULL);
	i = 0;
	t = 0;
	while (t < *size)
		if (!check_arg(av[++i]))
			res[t++] = atoi(av[i]);
	return (res);
}

int		*parse_args(int ac, char **av, int *size, int *opts)
{
	int	*res;
	int	i;

	res = NULL;
	i = 0;
	*opts = 0;
	while (++i < ac)
		if (!res && ft_strchr(av[i], ' ') && !(res = parse_split(av[i], size)))
			return (NULL);
		else if (check_arg(av[i]) == 1)
			*opts |= parse_opt(av[i]);
	if (!res)
		res = parse_all(ac, av, size);
	return (res);
}
