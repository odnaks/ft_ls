/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 14:53:44 by pcollio-          #+#    #+#             */
/*   Updated: 2019/03/08 20:07:22 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef FT_LS_H

# define FT_LS_H

# include <stdio.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <time.h>
# include "../libft/libft.h"
# include <grp.h>
# include <unistd.h>
# include <stdbool.h>
# include <ctype.h>
# include <sys/ioctl.h>
# include <errno.h>
# include <sys/xattr.h>
# include <sys/acl.h>

typedef struct s_ls {
	int		l;
	int		r;
	int		l_r;
	int		a;
	int		t;

	char	**args;
	int		index;
	char	**files;
	int		index_f;
	char	**dir;
	int		index_d;
	int		max;
	int		rec;
}				t_ls;

int			init_struct(t_ls *ls);
int			obj_type(const char* path);
void		put_usage(char a);
int			max_rows(int columns, int amount);
int			flags(char *args, t_ls *ls);
void		malloc_dir(int n, t_ls *ls);
void		malloc_files(int n, t_ls *ls);
int			get_time(char *f1, char *f2);
void		free_files(t_ls *ls);
void		free_dirs(t_ls *ls);
int			ft_strlen_two(char **a);
int			count_files(const char* path);
int			parcer(t_ls *ls, int argc, char **argv);
int			is_exist(const char* path);
int			get_attr(const char* path);

#endif
