#include "../includes/ft_ls.h"

int		count_files(const char* path)
{
	DIR *d;
	int count;
	struct dirent *dir;
	count = 0;

	d = opendir(path);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
			count++; // printf("%s\n", dir->d_name);
		closedir(d);
	}
	return (count);
}

int push_files(char *args, t_ls *ls)
{
	int len = ft_strlen(args);

	if (len > ls->max)
		ls->max = len;
	ls->files[ls->index_f] = malloc(sizeof(char) * (len + 1));
	ls->files[ls->index_f][len] = '\0';
	int i = 0;
	while (i < len)
	{
		ls->files[ls->index_f][i] = args[i];
		i++;
	}
	(ls->index_f)++;
	return (0);
}

int push_dir(char *args, t_ls *ls)
{
	int len = ft_strlen(args);

	ls->dir[ls->index_d] = malloc(sizeof(char) * (len + 1));
	ls->dir[ls->index_d][len] = '\0';
	int i = 0;
	while (i < len)
	{
		ls->dir[ls->index_d][i] = args[i];
		i++;
	}
	(ls->index_d)++;
	return (0);
}

int sort(t_ls *ls)
{
	int i;
	int j;

	i = 0;
	while (i < ls->index_f - 1)
	{
		j = i + 1;
		while (j < ls->index)
		{
			if (ls->t)
			{
				if (get_time ((ls->files[i]), (ls->files[j])) > 0)
				{
					char *tmp = ls->files[i];
					ls->files[i] = ls->files[j];
					ls->files[j] = tmp;
				}
			}
			else
			{
				if (ft_strcmp((ls->args[i]), (ls->args[j])) > 0)
				{
					char *tmp = ls->files[i];
					ls->files[i] = ls->files[j];
					ls->files[j] = tmp;
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

int parcer(t_ls *ls, int argc, char **argv)
{
	int i = 1;
	while (argc > 1 && flags(argv[i], ls) == 1)
	{
		argc--;
		i++;
	}

	//ф-ия, которая считает кол-во файлов и директори
	int	c_f = 0;
	int	c_d = 0;
	int	j = i;
	int temp_argc = argc;
	while (temp_argc > 1)
	{
		if (obj_type(argv[j]) == 0)
			c_f++;
		else
			c_d++;
		j++;
		temp_argc--;
	}
	if (c_f > 0)
		malloc_files(c_f, ls);
	if (c_d > 0)
		malloc_dir(c_d, ls);
	/* 
	if (argc > 1)
	{
		int n = argc;
		malloc_files(n, ls);
	} */
	while (argc > 1)
	{
		//file or dir
		//printf("%d\n", obj_type(argv[i]));
		int z = obj_type(argv[i]);
		if (!z)
			push_files(argv[i], ls);
		else
			push_dir(argv[i], ls);
		argc--;
		i++;
	}
	return (0);
}

int	format_rows(t_ls *ls)
{
	//printf("test\n");
	struct winsize w;
	int width;
	
	ioctl(0, TIOCGWINSZ, &w);
	width = w.ws_col;
	
	int max = ls->max;
	max = ls->max + (8 - (ls->max % 8));
	int count_col = width / max;

	int max_row = max_rows(count_col, ls->index_f);

	int i = 0;
	int j;
	while (i < max_row)
	{
		int k = 0;
		while (k < count_col)
		{
			j = i + k * max_row;
			if (j < ls->index_f)
				printf("%-*s", max, ls->files[j]);
			k++;
		}
		printf("\n");
		i++;
	}

	return (0);
}

void ls_files(t_ls *ls)
{
	sort(ls);
	format_rows(ls);
	//рекурсивная ф
}

void free_files(t_ls *ls)
{
	int i = 0;
	while (i < ls->index_f)
	{
		free(ls->files[i]);
		i++;
	}
	free(ls->files);
}

void		push_dir_files(char *path, t_ls *ls)//, t_ls *ls
{
	DIR *d;
	int count;
	struct dirent *dir;
	count = 0;

	
	d = opendir(path);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
			if (dir->d_name[0] != '.')
				push_files(dir->d_name, ls);
		ls_files(ls);
			//printf("%s\n", dir->d_name);//count++; // printf("%s\n", dir->d_name);
		closedir(d);
	}
}

void	ls_dir(t_ls *ls)
{
	int k = 0;
	int n = 0;
	while (k < ls->index_d)
	{
		n = count_files(ls->dir[k]) - 2;
		free_files(ls);
		malloc_files(n, ls);
		printf("\n%s:\n", ls->dir[k]);
		push_dir_files(ls->dir[k], ls);
		//printf("\n");
		k++;
	}
}

int ft_strlen_two(char **a)
{
	int i = 0;
	while (a[i])
		i++;
	return (i);
}

char **sort_rec(char **a, t_ls *ls)
{
	int i;
	int j;

	i = 0;
	/* char **temp;
	temp = a; */

	int n = ft_strlen_two(a);
	while (i < n - 1)
	{
		j = i + 1;
		while (j < n)
		{
			if (ls->t)
			{
				if (get_time ((a[i]), (a[j])) > 0)
				{
					char *tmp = a[i];
					a[i] = a[j];
					a[j] = tmp;
				}
			}
			else
			{
				if (ft_strcmp((a[i]), (a[j])) > 0)
				{
					char *tmp = a[i];
					a[i] = a[j];
					a[j] = tmp;
				}
			}
			j++;
		}
		i++;
	}
	return (a);
}

void	format_rows_rec(char **a)
{
	//printf("test\n");
	struct winsize w;
	int width;
	
	ioctl(0, TIOCGWINSZ, &w);
	width = w.ws_col;
	
	int max = ls->max;
	max = ls->max + (8 - (ls->max % 8));
	int count_col = width / max;

	int max_row = max_rows(count_col, ls->index_f);

	int i = 0;
	int j;
	while (i < max_row)
	{
		int k = 0;
		while (k < count_col)
		{
			j = i + k * max_row;
			if (j < ls->index_f)
				printf("%-*s", max, ls->files[j]);
			k++;
		}
		printf("\n");
		i++;
	}
}

void	ls_rec(/*char **a,*/ t_ls *ls, char *name)
{
	int i = 0;

	//открывает текущую директрию и записывает всё содержимое с массив, молоча
	a = sort_rec(a);
	format_rows_rec(s);
	int n = ft_strlen_two(a);
	while (i < n)
	{
		if (obj_type(a[i]) == 1)
		{
			char *tmp = a[i];
			tmp = ft_strjoin(tmp, "/");
			name = ft_strjoin(name, tmp);
			ls_rec(a, ls, name);ды 
		}
		i++;
	}

}

char	**files_to_str(t_ls *ls)
{
	char **a;
	int i = 0;
	a = malloc(sizeof(char*) * (ls->index_f + 1));
	a[ls->index_f] = 0;
	while (i < ls->index_f)
	{
		a[i] = malloc(sizeof(char) * ft_strlen(ls->files[i] + 1));
		int j = 0;
		while (j < (int)ft_strlen(ls->files[i]))
		{
			a[i][j] = ls->files[i][j];
			j++;
		}
		a[i][j] = '\0';
		i++;
	}
	free_files(ls);
	return (a);
}

int	ft_ls(t_ls *ls, int argc, char **argv)
{
	parcer(ls, argc, argv);
	ls_files(ls);
	ls_dir(ls);
	char **a;
	if (ls->l_r)
	{
		//a = files_to_str(ls);
		//ls_rec(a, ls, ".");
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_ls ls;
	init_struct(&ls);
	ft_ls(&ls, argc, argv);

	/* 
	test pars
	printf("flags:\n-l: %d   -r: %d   -R %d   -a %d   -t %d\n\n", ls.l, ls.r, ls.l_r, ls.a, ls.t);
	int i = 0;
	while (i < ls.index)
	{
		printf("files:\n%s\n", ls.args[i]);
		i++;
	} */
	return (0);
}