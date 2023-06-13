#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
	int i = 1;

	printf ("amount of arguments: %d\n", argc - 1);
	while (i < argc)
	{
		if (i == argc - 1)
			i += 2;
		printf("arg n0 %d: %s\n", i, argv[i]);
		i++;
	}
	return 0;
}