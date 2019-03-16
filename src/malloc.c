/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcollio- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 11:13:09 by pcollio-          #+#    #+#             */
/*   Updated: 2019/03/14 20:37:45 by pcollio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		init_struct(t_ls *ls)
{
	ls->l = 0;
	ls->r = 0;
	ls->l_r = 0;
	ls->l_a = 0;
	ls->a = 0;
	ls->t = 0;
	ls->o = 0;
	ls->f = 0;
	ls->n = 0;
	ls->one = 0;
	ls->index = 0;
	ls->max = 0;
	ls->index_f = 0;
	ls->index_d = 0;
	ls->rec = 0;
	ls->max = 0;
	ls->er = 0;
	ls->path = 0;
}

void		malloc_dir(int n, t_ls *ls)
{
	ls->dir = malloc(sizeof(char*) * (n + 1));
	ls->dir[n] = NULL;
	ls->index_d = 0;
}

void		malloc_files(int n, t_ls *ls)
{
	ls->files = malloc(sizeof(char*) * (n + 1));
	ls->files[n] = NULL;
	ls->index_f = 0;
}

void		free_files(t_ls *ls)
{
	int	i;

	i = 0;
	while (i < ls->index_f)
	{
		free(ls->files[i]);
		i++;
	}
	free(ls->files);
}

void		free_dirs(t_ls *ls)
{
	int i;

	i = 0;
	while (i < ls->index_d)
	{
		free(ls->dir[i]);
		i++;
	}
	free(ls->dir);
}
