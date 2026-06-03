#include "../push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	a;
	t_stack	b;

	if (argc < 2)
		return (0);

	// 1. ініціалізація стеків
	init_stack(&a);
	init_stack(&b);

	// 2. перевірка / парсинг аргументів
	if (!parse_args(&a, argv + 1))
		return (write(2, "Error\n", 6), 1);

	// 3. якщо вже відсортовано — нічого не робимо
	if (is_sorted(&a))
		return (0);

	// 4. запуск алгоритму сортування
	sort_stack(&a, &b);

	// 5. очищення памʼяті
	free_stack(&a);
	free_stack(&b);

	return (0);
}