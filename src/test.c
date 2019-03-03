#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>

int		obj_type(const char* path)
{
	struct stat path_stat;

	lstat(path, &path_stat);
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


// int		get_type(int a, int b)
// {
// 	if ((a & S_IFMT) == b)
// 		return (1);
// 	return (0);
// }

// int		obj_type(const char* path)
// {
// 	struct stat path_stat;

// 	lstat(path, &path_stat);
// 	// printf("%d", path_stat.st_mode);
// 	if (get_type(path_stat.st_mode, S_IFREG))
// 		return (0); //regular file
// 	else if (get_type(path_stat.st_mode, S_IFDIR))
// 		return(1); //directory
// 	else if (get_type(path_stat.st_mode, S_IFCHR))
// 		return(2); //character device
// 	else if (get_type(path_stat.st_mode, S_IFBLK))
// 		return(3); //block device
// 	else if (get_type(path_stat.st_mode, S_IFIFO))
// 		return(4); //FIFO/pipe
// 	else if (get_type(path_stat.st_mode, S_IFLNK))
// 		return(5); //symlink
// 	else if (get_type(path_stat.st_mode, S_IFSOCK))
// 		return(7); //socket
// 	else
// 		return(-1); //unknown
// 	return(0);
// }


// (sp->st_mode)
// #define	S_ISBLK(m)	(((m) & S_IFMT) == S_IFBLK)	/* block special */
// #define	S_ISCHR(m)	(((m) & S_IFMT) == S_IFCHR)	/* char special */
// #define	S_ISDIR(m)	(((m) & S_IFMT) == S_IFDIR)	/* directory */
// #define	S_ISFIFO(m)	(((m) & S_IFMT) == S_IFIFO)	/* fifo or socket */
// #define	S_ISREG(m)	(((m) & S_IFMT) == S_IFREG)	/* regular file */
// #define	S_ISLNK(m)	(((m) & S_IFMT) == S_IFLNK)	/* symbolic link */
// #define	S_ISSOCK(m)	(((m) & S_IFMT) == S_IFSOCK)	/* socket */


int main(int argc, char **argv, char **envp)
{
	
	printf("\n%d", obj_type("."));
//	printf("%d", c);




//printf("%s\n", dir->d_name);


/* 	DIR *a;
	struct dirent *entry;

	a = opendir("/Users/pcollio-/Projects/ft_ls/test");

	while ((entry = readdir(a)))
	{
		ft_printf("%lld - %s [%d] %d %d %lld\n",
			   entry->d_ino, entry->d_name, entry->d_type, entry->d_reclen, entry->d_namlen, entry->d_seekoff);
	}
*/

//	struct stat f1;
//	struct stat f2;
//
//	stat("test", &f1);
	// printf( (S_ISDIR(s.st_mode)) ? "d" : "-");
   // printf( (s.st_mode & S_IRUSR) ? "r" : "-");
   // printf( (s.st_mode & S_IWUSR) ? "w" : "-");
   // printf( (s.st_mode & S_IXUSR) ? "x" : "-");
   // printf( (s.st_mode & S_IRGRP) ? "r" : "-");
   // printf( (s.st_mode & S_IWGRP) ? "w" : "-");
   // printf( (s.st_mode & S_IXGRP) ? "x" : "-");
   // printf( (s.st_mode & S_IROTH) ? "r" : "-");
   // printf( (s.st_mode & S_IWOTH) ? "w" : "-");
   // printf( (s.st_mode & S_IXOTH) ? "x" : "-");
	// time_t lt;
	// lt = time(NULL);
	// printf("%s", ctime(&lt));


	// printf("test = %ld\n\n", f1.st_ctime);
	// stat("libft", &f2);
	// printf("libf = %ld\n", f2.st_ctime);


//    printf ("columns %d\n", width);
// int amount = 10;
// int column = 3;

// 		if (amount % column)
// 			printf("%d \n",((amount / column) + 1));
// 		printf("%d \n",(amount / column));
}