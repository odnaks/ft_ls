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

int		is_file(const char* name)
{
	DIR* directory;

	opendir(name);
	if (directory != NULL)
	{
		closedir(directory);
		return (2);
	}
	if (errno == ENOTDIR)
		return (1);
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

int files(char *args, t_ls *ls)
{
	int len = ft_strlen(args);

	if (len > ls->max)
		ls->max = len;
	ls->args[ls->index] = malloc(sizeof(char) * (len + 1));
	ls->args[ls->index][len] = '\0';
	int i = 0;
	while (i < len)
	{
		ls->args[ls->index][i] = args[i];
		i++;
	}
	(ls->index)++;
	return (0);
}

void malloc_files(int n, t_ls *ls)
{
	ls->args = malloc(sizeof(char*) * n);
	ls->args[n] = NULL;
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
	while (i < ls->index - 1)
	{
		j = i + 1;
		while (j < ls->index)
		{
			if (ls->t)
			{
				if (get_time ((ls->args[i]), (ls->args[j])) > 0)
				{
					char *tmp = ls->args[i];
					ls->args[i] = ls->args[j];
					ls->args[j] = tmp;
				}
			}
			else
			{
				if (ft_strcmp((ls->args[i]), (ls->args[j])) > 0)
				{
					char *tmp = ls->args[i];
					ls->args[i] = ls->args[j];
					ls->args[j] = tmp;
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
	


	if (argc > 1)
	{
		int n = argc;
		malloc_files(n, ls);
	}
	while (argc > 1)
	{
		files(argv[i], ls);
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

	int max_row = max_rows(count_col, ls->index);

	int i = 0;
	int j;
	while (i < max_row)
	{
		int k = 0;
		while (k < count_col)
		{
			j = i + k * max_row;
			if (j < ls->index)
				printf("%-*s", max, ls->args[j]);
			k++;
		}
		printf("\n");
		i++;
	}


	return (0);
}


int	ft_ls(t_ls *ls, int argc, char **argv)
{
	parcer(ls, argc, argv);

	//делит на 2 массива

	
	sort(ls);
	format_rows(ls);

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