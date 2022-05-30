#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char *p = NULL;
	p = get_next_line(fd);
	while (p != NULL)
	{
		printf("%s", p);
		p = get_next_line(fd);
	}	
}
