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

int		char_exist(char *s, int len, char c)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (-1);
}

void	ft_inter(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i])
	{
		if (char_exist(s1, i, s1[i]) == -1 &&
			char_exist(s1, ft_strlen(s2), s1[i]) == 1)
			ft_putchar(s1[i]);
		i++;
	}
}

int		main(int ac, char **av)
{
	if (ac == 3)
	{
		ft_inter(av[1], av[2]);
	}
	ft_putchar('\n');
	return (0);
}
