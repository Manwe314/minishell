#include <stdio.h>

int main(int argc, char **argv)
{
	int i = 1;
	printf ("amount of arguments: %d\n", argc - 1);
	while (i < argc)
	{
		printf("arg n0 %d: %s\n", i, argv[i]);
		i++;
	}
	return 0;
}