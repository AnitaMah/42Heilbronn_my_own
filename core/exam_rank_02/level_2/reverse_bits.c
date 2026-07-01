unsigned char	reverse_bits(unsigned char octet)
{
    unsigned char	res;
    int				index;

	index = 8;
	res = 0;
	while (index > 0)
	{
		res = res * 2 + (octet % 2);
		octet = octet / 2;
		index--;
	}
	return (res);
}