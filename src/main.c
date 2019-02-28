#include "../includes/ft_ls.h"

int	init_struct(t_ls *ls)
{
	ls->l = 0;
	ls->r = 0;
	ls->l_r = 0;
	ls->a = 0;
	ls->t = 0;
	ls->index = 0;
	ls->max = 0;
	ls->index_f = 0;
	ls->index_d = 0;

	return (0);
}

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
			count++;
		closedir(d);
	}
	return (count);
}

// int		is_file(const char* name)
// {
// 	DIR* directory;

// 	opendir(name);
// 	if (directory != NULL)
// 	{
// 		closedir(directory);
// 		return (2);
// 	}
// 	if (errno == ENOTDIR)
// 		return (1);
// }
int		obj_type(const char* path)
{
	struct stat path_stat;
	stat(path, &path_stat);

	if ((path_stat.st_mode & S_IFMT) == S_IFREG)
		return (0); //regular file
	else if ((path_stat.st_mode & S_IFMT) == S_IFDIR)
		return(1); //directory
	else if ((path_stat.st_mode & S_IFMT) == S_IFCHR)
		return(2); //character device
	else if ((path_stat.st_mode & S_IFMT) == S_IFBLK)
		return(3); //block device
	else if ((path_stat.st_mode & S_IFMT) == S_IFIFO)
		return(4); //FIFO/pipe
	else if ((path_stat.st_mode & S_IFMT) == S_IFLNK)
		return(5); //symlink
	else if ((path_stat.st_mode & S_IFMT) == S_IFSOCK)
		return(7); //socket
	else
		return(-1); //unknown
}

void	put_usage(char a)
{
	printf("ls: illegal option -- %c\n", a);
	printf("usage: ls [-lrRat] [file ...]");
	exit(1);
}

int		max_rows(int columns, int amount)
{
	if (amount % columns)
		return ((amount / columns) + 1);
	return (amount / columns);
}

int	flags(char *args, t_ls *ls)
{
	int i = 0;
	if (args[i] == '-' && args[i + 1] > 32 && args[i + 1] < 127)
	{
		i++;
		while (args[i] > 32 && args[i] < 127)
		{
			if (args[i] == 'l')
				ls->l = 1;
			else if (args[i] == 'r')
				ls->r = 1;
			else if (args[i] == 'R')
				ls->l_r = 1;
			else if (args[i] == 'a')
				ls->a = 1;
			else if (args[i] == 't')
				ls->t = 1;
			else
				put_usage(args[i]);
			i++;
		}
		return (1);
	}
	return (0);
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

void malloc_dir(int n, t_ls *ls)
{
	ls->dir = malloc(sizeof(char*) * (n + 1));
	ls->dir[n] = NULL;
	ls->index_d = 0;
}

void malloc_files(int n, t_ls *ls)
{
	ls->files = malloc(sizeof(char*) * (n + 1));
	ls->files[n] = NULL;
	ls->index_f = 0;
}

int get_time(char *f1, char *f2)
{
	struct stat s1;
	struct stat s2;
 
	stat(f1, &s1);
	stat(f2, &s2);
 
	if (s1.st_ctime > s2.st_ctime)
		return (1);
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
		printf("%d\n", obj_type(argv[i]));
		if (obj_type(argv[j]) == 0)
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
}

/* void ls_dir(t_ls *ls)
{

} */


int	ft_ls(t_ls *ls, int argc, char **argv)
{
	parcer(ls, argc, argv);
	//делит на 2 массива

	ls_files(ls);
	//ls_dir(ls);

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