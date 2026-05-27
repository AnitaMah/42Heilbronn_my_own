
int is_valid_number(char *str)
{
    int i;

	i = 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
    if (!str[i])
        return (0);
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

int is_positiv(int nb)
{
    if (nb < 0)
        return (0);
    return (1);
}

int is_prime(int nb)
{
    int i = 2;

    if (nb < 2)
        return (0);
    while (i <= nb / i)
    {
        if (nb % i == 0)
            return (0);
        i++;
    }
    return (1);
}

void	put_nbr(int nb)
{
	char c;

	if (nb >= 10)
		put_nbr(nb / 10);
	c = (nb % 10) + '0';
	write(1, &c, 1);
}

int calculate_a_sign(char *str, int *iter)
{
    int sign = 1;
    if (str[*iter] == '-')
    {
        sign = -1;
    }
    (*iter)++;
    return (sign);
}
int calculate_a_base(char *str, int *iter)
{
    int res;

    res = 0;
    while (str[*iter] >= '0' && str[*iter] <= '9')
    {
        res = res * 10 + str[*iter] - '0';
        (*iter)++;
    }
    return (res);
}

int ft_atoi(char *str)
{
    int iter = 0;
    int sign;
    int res;
    sign = calculate_a_sign(str, &iter);
    res = calculate_a_base(str, &iter);
    return (sign * res);
}

void	add_prime_sum(int nb)
{
    int sum;
    int i;

    sum = 0;
    i = 2;
    while (i <= nb)
    {
        if (is_prime(i))
            sum += i;
        i++;
    }
    put_nbr(sum);
    
}

int main(int argc, char **argv)
{
    int nb;
    if (argc == 2)
    {
		if (is_valid_number(argv[1]))
		{
        	nb = ft_atoi(argv[1]);
            if (nb > 0)
				add_prime_sum(nb);
			else
				write(1, "0", 1);

		}
    }
	else
		write(1, "0", 1);
    write (1, "\n", 1);
    return (0);
}