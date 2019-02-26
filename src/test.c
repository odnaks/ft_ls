#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

/* 
S_ISDIR == directory
S_ISFIFO == fifo or socket
S_ISREG == regular file
S_ISLNK == symbolic link
S_ISSOCK == socket
*/

int		file_type(const char* path)
{
	struct stat path_stat;
	stat(path, &path_stat);

	switch (path_stat.st_mode & S_IFMT) 
	{
		case S_IFBLK:
			printf("block device\n");
			break;
		case S_IFCHR:
			printf("character device\n");
			break;
		case S_IFDIR:
			printf("directory\n");
			break;
		case S_IFIFO:
			printf("FIFO/pipe\n");
			break;
		case S_IFLNK:
			printf("symlink\n");
			break;
		case S_IFREG:
			printf("regular file\n");
			break;
		case S_IFSOCK:
			printf("socket\n");
			break;
		default:
			printf("unknown?\n");
			break;
	}
}

int main(int argc, char **argv, char **envp)
{



	file_type("src/main.c");










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