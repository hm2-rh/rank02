#include <unistd.h>

void	ft_putchar(int c)
{
	write(1, &c, 1);
}

int		ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int		char_exist(char *s, int pos, char c)
{
	int i;

	i = 0;
	while (i < pos)
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (-1);
}

void	ft_union(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i])
	{
		if (char_exist(s1, i, s1[i]) == -1)
			ft_putchar(s1[i]);
		i++;
	}
	i = 0;
	while (s2[i])
	{
		if (char_exist(s1, ft_strlen(s1), s2[i]) == -1 &&
			char_exist(s2, i, s2[i]) == -1)
			ft_putchar(s2[i]);

		i++;
	}
}

int		main(int ac, char **av)
{
	if (ac == 3)
	{
		ft_union(av[1], av[2]);
	}
	ft_putchar('\n');
	return (1);
}
