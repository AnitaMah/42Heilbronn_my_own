#include "tester.h"

void	init_stats(t_stats *s)
{
	s->min = 1000000;
	s->max = 0;
	s->total = 0;
	s->tests = 0;
	s->failed = 0;
}

void	update_stats(t_stats *s, int ops)
{
	if (ops < s->min)
		s->min = ops;
	if (ops > s->max)
		s->max = ops;
	s->total += ops;
	s->tests++;
}
