
int	max(int* tab, unsigned int len)
{
	int	max;
	int	iter;

	if (!tab || len == 0)
		return (0);
	max = tab[0];
	iter = 1;
	while (iter < len)
	{
		if (tab[iter] > max)
		{
			max = tab[iter];
		}
		iter++;
	}
	return (max);
}