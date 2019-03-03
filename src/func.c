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