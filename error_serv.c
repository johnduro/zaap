
#include "stdlib.h"
#include "zaap.h"
#include "libft.h"

int	zaap_error(int code)
{
	if (code == -1)
	{
		ft_putstr_fd(USAGE1, 2);
		ft_putstr_fd(USAGE2, 2);
	}
	else if (code == -2)
		ft_putstr_fd("Malloc error\n", 2);
	else if (code == -3)
		ft_putstr_fd("Team name too long\n", 2);
	else if (code == -4)
		ft_putstr_fd("Minimum size for x or y is 20\n", 2);
	else if (code == -5)
		ft_putstr_fd("Wrong port number\n", 2);
	else if (code == -6)
		ft_putstr_fd("Sock error\n", 2);
	else if (code == -7)
		ft_putstr_fd("Bind error\n", 2);
	exit(code);
}
