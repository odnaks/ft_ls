#include "../includes/ft_ls.h"

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
		while (j < ls->index_f)
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
				if (ft_strcmp((ls->files[i]), (ls->files[j])) > 0)
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
	if (ls->r)
	{
		i = 0;
		int med = ls->index_f / 2;
		while (i < med)
		{
			char *tmp = ls->files[i];
			ls->files[i] = ls->files[ls->index_f - 1 - i];
			ls->files[ls->index_f -1 - i] = tmp;
			i++;
		}
	}
	return (0);
}

int	format_rows(t_ls *ls)
{
	struct winsize w;
	int width;
	
	ioctl(0, TIOCGWINSZ, &w);
	width = w.ws_col;
	
	int max = ls->max + (8 - (ls->max % 8));
	//int max = ls->max + 1;
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
		closedir(d);
	}
}

void	ls_dir(t_ls *ls)
{
	int k = 0;
	int n = 0;
	while (k < ls->index_d)
	{
		n = count_files(ls->dir[k], ls);
		free_files(ls);
		malloc_files(n, ls);
		printf("\n%s:\n", ls->dir[k]);
		push_dir_files(ls->dir[k], ls);
		k++;
	}
}

char **dir_to_str(t_ls *ls)
{
	int i = 0;
	char **str;
	str = malloc(sizeof(char*) * (ls->index_d + 1));
	str[ls->index_d] = 0;
	while (i < ls->index_d)
	{
		str[i] = malloc(sizeof(char) * ft_strlen(ls->dir[i] + 1));
		int j = 0;
		while (j < (int)ft_strlen(ls->dir[i]))
		{
			str[i][j] = ls->dir[i][j];
			j++;
		}
		str[i][j] = '\0';
		i++;
	}
	free_dirs(ls);
	return (str);
}

char **push_dir_files_to_str(char *path, char **obj, t_ls *ls)
{
	DIR *d;
	int count;
	struct dirent *dir;
	count = 0;

	d = opendir(path);
	int i = 0;
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (dir->d_name[0] != '.' || ls->a)
			{
				char *file = dir->d_name;
				int n = strlen(file);
				if (n > ls->max)
					ls->max = n;
				obj[i] = malloc(sizeof(char) * (n + 1));
				obj[i][n] = '\0';
				int j = 0;
				while (j < n)
				{
					obj[i][j] = file[j];
					j++;
				}
				i++;
			}
		}
		closedir(d);
	}
	return (obj);
}

int	format_rows_objs(char **objs, int n, t_ls *ls)
{
	struct winsize w;
	int width;
	
	ioctl(0, TIOCGWINSZ, &w);
	width = w.ws_col;
	int max = ls->max + (8 - (ls->max % 8));
	int count_col = width / max;
	int max_row = max_rows(count_col, n);
	int i = 0;
	int j;
	while (i < max_row)
	{
		int k = 0;
		while (k < count_col)
		{
			j = i + k * max_row;
			if (j < n)
				printf("%-*s", max, objs[j]);
			k++;
		}
		printf("\n");
		i++;
	}
	return (0);
}

char **sort_objs(char **obj, int n, t_ls *ls)
{
	int i;
	int j;

	i = 0;
	while (i < n - 1)
	{
		j = i + 1;
		while (j < n)
		{
			if (ls->t)
			{
				if (get_time ((obj[i]), (obj[j])) > 0)
				{
					char *tmp = obj[i];
					obj[i] = obj[j];
					obj[j] = tmp;
				}
			}
			else
			{
				if (ft_strcmp((obj[i]), (obj[j])) > 0)
				{
					char *tmp = obj[i];
					obj[i] = obj[j];
					obj[j] = tmp;
				}
			}
			j++;
		}
		i++;
	}
	if (ls->r)
	{
		i = 0;
		int med = n / 2;
		n--;
		while (i < med)
		{
			char *tmp = obj[i];
			obj[i] = obj[n - i];
			obj[n - i] = tmp;
			i++;
		}
	}
	return (obj);
}

void	ls_rec(char *str, t_ls *ls)
{
	ls->max = 0;
	if (ls->rec || ls->index_f)
		printf("\n%s:\n", str);
	else if (ls->index_d > 1 || ls->er)
		printf("%s:\n", str);
	int n = count_files(str, ls);
	char **objs;
	objs = malloc(sizeof(char*) * (n + 1));
	objs[n] = 0;
	objs = push_dir_files_to_str(str, objs, ls);
	objs = sort_objs(objs, n, ls);
	format_rows_objs(objs, n, ls);
	ls->rec++;
	if (ls->l_r)
	{
		ls->rec++;
		int i = 0;
		while (i < n)
		{
			char *a;
			a = ft_strjoin(str, "/");
			a = ft_strjoin(a, objs[i]);
			if (obj_type(a) == 1)
			{
				if (!(objs[i][0] == '.' && objs[i][1] == '\0')
					&& !(objs[i][0] == '.' && objs[i][1] == '.'))
					ls_rec(a, ls);
			}
			i++;
		}
	}
}

int parcer(t_ls *ls, int argc, char **argv)
{
	int i = 1;
	while (argc > 1 && flags(argv[i], ls) == 1)
	{
		argc--;
		i++;
	}
	int	c_f = 0;
	int	c_d = 0;
	int	j = i;
	int temp_argc = argc;
	while (temp_argc > 1)
	{
		if (is_exist(argv[j]) == 0)
		{
			printf("ls: %s: No such file or directory\n", argv[j]);
			ls->er = 1;
		}
		else if (obj_type(argv[j]) == 0)
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
	if (c_f == 0 && c_d == 0 && ls->er == 0)
	{
		malloc_dir(1, ls);
		push_dir(".", ls);
		return (0);
	}
	while (argc > 1)
	{
		int z = obj_type(argv[i]);
		if (is_exist(argv[i]))
		{
			if (!z)
				push_files(argv[i], ls);
			else
				push_dir(argv[i], ls);
		}
		argc--;
		i++;
	}
	return (0);
}

int	ft_ls(t_ls *ls, int argc, char **argv)
{
	parcer(ls, argc, argv);
	ls_files(ls);
	char **a = dir_to_str(ls);
	int n = ft_strlen_two(a);
	a = sort_objs(a, n, ls);
	int i = 0;
	while(i < n)
	{
		ls_rec(a[i], ls);
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_ls ls;
	init_struct(&ls);
	ft_ls(&ls, argc, argv);

	return (0);
}
