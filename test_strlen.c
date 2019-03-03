#include <stdio.h>
#include <stdlib.h>


int ft_strlen_two(char **a)
{
	int i = 0;
	while (a[i])
		i++;
	return (i);
}

int main()
{
    char **a;
    a = malloc(sizeof(char*) * 3);
    a[0] = malloc(sizeof(char) * 5);
    a[0] = "test";
    a[1] = malloc(sizeof(char) * 5);
    a[1] = "test";
    a[2] = malloc(sizeof(char) * 5);
    a[2] = "test";
    a[3] = 0;
    printf("%d\n", ft_strlen_two(a));
}