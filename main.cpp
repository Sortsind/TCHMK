#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(int argc, char* argv[])
{
	char *file1 = argv[1];
	char *file2 = argv[3];
	char *file3 = argv[4];
	char *file4 = NULL;
	bool flag = 0;
	bool flag_mul = 0;
	bool flag_sum = 0;
	bool flag_sub = 0;
	int bin = 0;
	if (argc == 6)
	{
		if (!strcmp(argv[5], "-b"))
			bin = 1;
		else
			file4 = argv[5];
	}

	if (argc == 7)
	{
		bin = 1;
		file4 = argv[6];
	}

	long_numeric A, B, mod;

	if (bin == 1)
	{
		A = read_bin_file(file1);
		B = read_bin_file(file2);
		if (file4 != NULL)
			mod = read_bin_file(file4);
	}
	else
	{
		A = read_file(file1);
		B = read_file(file2);
		if (file4 != NULL)
			mod = read_file(file4);
	}

	struct long_numeric c;
	c.size = 0;
	c.sign = 0;
	c.digits = NULL;
	if (argv[2][0] == '+')
	{
		c = sum_and_sub(A, B);
		flag_sum = 1;
	}

	if (argv[2][0] == '-')
	{
		flag_sub = 1;
		long_numeric minusB = minus(B);
		c = sum_and_sub(A, minusB);
		free(minusB.digits);
	}

	if (argv[2][0] == '*')
	{
		c = multiplication(A, B);
		flag_mul = 1;
	}

	if (argv[2][0] == '/')
	{
		long_numeric q;
		c = dividing(A, B, &q);
		flag = 1;
		free(q.digits);
	}

	if (argv[2][0] == '%')
	{
		long_numeric q = dividing(A, B, &c);
		free(q.digits);
	}

	if (file4 != NULL)
	{
		long_numeric tmp;
		long_numeric q = dividing(c, mod, &tmp);
		free(q.digits);
		free(c.digits);
		c = tmp;
	}

	if (argv[2][0] == '^')
	{
		if (file4 == NULL)
			c = involution(A, B);
		else
			c = involution_module(A, B, mod);
	}

	if (bin == 1)
		write_bin_file(file3, c, flag, flag_mul, flag_sum, flag_sub);
	else
		write_file(file3, c);

	free(A.digits);
	free(B.digits);
	free(c.digits);
	if (file4 != NULL)
		free(mod.digits);

	return 0;
}