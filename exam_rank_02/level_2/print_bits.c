#include <unistd.h>

void	print_bits(unsigned char octet)
{
	int				index;
	unsigned char	res;

	index = 8;
	while ((--index) > 0)
	{
		res = (octet >> index & 1) + '0';
		write(1, &res, 1);
	}
}