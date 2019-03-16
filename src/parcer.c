/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 13:47:04 by drestles          #+#    #+#             */
/*   Updated: 2019/03/16 00:24:40 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int	parse_help(t_ls *ls, char a)
{
	if (a == 't')
		ls->t = 1;
	else if (a == 'o')
		ls->o = 1;
	else if (a == '1')
		ls->one = 1;
	else if (a == 'f')
	{
		ls->f = 1;
		ls->a = 1;
	}
	else if (a == 'n')
	{
		ls->n = 1;
		ls->l = 1;
	}
	else
		put_usage(a);
	return (0);
}

void		parse_flags(t_ls *ls, char a)
{
	if (a == 'l')
		ls->l = 1;
	else if (a == 'r')
		ls->r = 1;
	else if (a == 'R')
		ls->l_r = 1;
	else if (a == 'A')
		ls->l_a = 1;
	else if (a == 'a')
		ls->a = 1;
	else if (parse_help(ls, a))
		;
}

static void	count_obj(int argc, char **argv, int j, t_ls *ls)
{
	while (argc > 1)
	{
		if (is_exist(argv[j]) == 0)
		{
			ft_printf("ls: %s: No such file or directory\n", argv[j]);
			ls->er = 1;
		}
		else if (obj_type(argv[j]) == 1)
			ls->c_d++;
		else
			ls->c_f++;
		j++;
		argc--;
	}
}

static void	push_objs(t_ls *ls, int argc, char **argv, int i)
{
	int	type;

	while (argc > 1)
	{
		type = obj_type(argv[i]);
		if (is_exist(argv[i]))
		{
			if (type == 1)
				push_dir(argv[i], ls);
			else
				push_files(argv[i], ls);
		}
		argc--;
		i++;
	}
}

int			parcer(t_ls *ls, int argc, char **argv)
{
	int	i;

	i = 1;
	while (argc > 1 && flags(argv[i], ls) == 1)
	{
		argc--;
		i++;
	}
	count_obj(argc, argv, i, ls);
	if (ls->c_f > 0)
		malloc_files(ls->c_f, ls);
	if (ls->c_d > 0)
		malloc_dir(ls->c_d, ls);
	if (ls->c_f == 0 && ls->c_d == 0 && ls->er == 0)
	{
		malloc_dir(1, ls);
		push_dir(".", ls);
		return (0);
	}
	push_objs(ls, argc, argv, i);
	return (0);
}
