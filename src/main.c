/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 10:01:40 by drestles          #+#    #+#             */
/*   Updated: 2019/03/10 15:35:32 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static char	**ls_rec_init(t_ls *ls, char *str, int *n)
{
	char **objs;

	ls->max = 0;
	if (ls->rec)
		free(ls->path);
	ls->path = ft_strjoin(str, "/");
	if (ls->rec || ls->index_f)
		printf("\n%s:\n", str);
	else if (ls->index_d > 1 || ls->er)
		printf("%s:\n", str);
	*n = count_files(str, ls);
	objs = malloc(sizeof(char*) * (*n + 1));
	objs[*n] = 0;
	objs = push_dir_files_to_str(str, objs, ls);
	objs = sort_objs(objs, *n, ls);
	return (objs);
}

static void	rec_rec(t_ls *ls, char *str, char **objs, int n)
{
	int		i;
	char	*a;

	i = 0;
	while (i < n)
	{
		a = ft_strjoin(str, "/");
		a = ft_strjoin_left(a, objs[i]);
		if (obj_type(a) == 1)
		{
			if (!(objs[i][0] == '.' && objs[i][1] == '\0')
				&& !(objs[i][0] == '.' && objs[i][1] == '.'))
				ls_rec(a, ls);
		}
		free(a);
		i++;
	}
}

void		ls_rec(char *str, t_ls *ls)
{
	char	**objs;
	int		n;

	objs = ls_rec_init(ls, str, &n);
	if (ls->l)
		l_format_rows_objs(objs, n, ls);
	else
		format_rows_objs(objs, n, ls);
	ls->rec++;
	if (ls->l_r)
	{
		ls->rec++;
		rec_rec(ls, str, objs, n);
	}
	free(objs);
}

int			ft_ls(t_ls *ls, int argc, char **argv)
{
	char	**a;
	int		n;
	int		i;

	parcer(ls, argc, argv);
	ls_files(ls);
	a = dir_to_str(ls);
	n = ft_strlen_two(a);
	a = sort_objs(a, n, ls);
	i = 0;
	while (i < n)
	{
		ls_rec(a[i], ls);
		i++;
	}
	return (0);
}

int			main(int argc, char **argv)
{
	t_ls ls;

	init_struct(&ls);
	ft_ls(&ls, argc, argv);
	return (0);
}
