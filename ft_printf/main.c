#include "includes/ft_printf.h"
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	int	ret;

	ret = ft_printf("character %s\n", "como estas todo bien");
	printf("ret = %d\n", ret);
	ret = printf("character %s\n", "como estas todo bien");
	printf("ret = %d\n", ret);
	/*close(1);
	//fflush(stdout);
	int fd = open("/dev/tty", O_WRONLY);
	if (fd < 0)
	{
		perror("open");
		return 1;
	}*/
	return 0;
}
