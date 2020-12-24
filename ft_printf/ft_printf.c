#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

#define I	f->i
#define MW	f->mwidth
#define PR	f->prec
#define	S	f->copy
#define	ARG	f->arg

int	g_ret = 0;

typedef	struct	s_form
{
	va_list	arg;
	char	*copy;
	int		i;
	int		mwidth;
	int		prec;
}				t_form;

int		ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int		ft_nbrlen_base(int d, unsigned base)
{
	int			len;
	unsigned	ud;

	len = 0;
	if (base == 10)
	{
		if (d < 0)
		{
			len++;
			d *= -1;
		}
	}
	ud = (unsigned)d;
	while (ud > 0)
	{
		len++;
		ud /= base;
	}
	return (len);
}

void	ft_putchar(int c)
{
	write(1, &c, 1);
	g_ret++;
}

void	ft_putnbr_base(int d, unsigned base)
{
	char		*dig;
	unsigned	ud;

	if (base == 10)
	{
		dig = "0123456789";
		if (d < 0)
		{
			ft_putchar('-');
			d *= -1;
		}
	}
	else if (base == 16)
		dig = "0123456789abcdef";
	ud = (unsigned)d;
	if (ud < base)
		ft_putchar(dig[ud]);
	if (ud >= base)
	{
		ft_putnbr_base(ud / base, base);
		ft_putchar(dig[ud % base]);
	}
}

void	print_s(t_form *f)
{
	char *s;
	int	len;
	int k;

	s = va_arg(ARG, char *);
	if (!s)
		s = "(null)";
	len = ft_strlen(s);
	if (PR > -1 && PR < len)
		len = PR;
	if (MW > len)
	{
		k = 0;
		while (k++ < MW - len)
			ft_putchar(' ');
	}
	k = 0;
	while (k < len)
		ft_putchar(s[k++]);
	I++;
}

void	print_d(t_form *f)
{
	int		d;
	int		len;
	int		k;

	d = va_arg(ARG, int);
	len = ft_nbrlen_base(d, 10);
	if (PR > len)
	{
		if (d < 0)
			MW--;
		k = 0;
		while (k++ < MW - PR)
			ft_putchar(' ');
		if (d < 0)
		{
			ft_putchar('-');
			len--;
			d *= -1;
		}
		k = 0;
		while (k++ < PR - len)
			ft_putchar('0');
	}
	else if (MW > len)
	{
		k = 0;
		while (k++ < MW - len)
			ft_putchar(' ');
	}
	ft_putnbr_base(d, 10);
	I++;
}

void	print_x(t_form *f)
{
	int		d;
	int		len;
	int		k;

	d = va_arg(ARG, int);
	len = ft_nbrlen_base(d, 16);
	if (PR > len)
	{
		k = 0;
		while (k++ < MW - PR)
			ft_putchar(' ');
		k = 0;
		while (k++ < PR - len)
			ft_putchar('0');
	}
	else if (MW > len)
	{
		k = 0;
		while (k++ < MW - len)
			ft_putchar(' ');
	}
	ft_putnbr_base(d, 16);
	I++;
}

int		ft_printf(const char *format, ...)
{
	t_form *f;

	f = malloc(sizeof(t_form));
	S = (char *)format;
	I = 0;
	if (format)
	{
		va_start(ARG, format);
		while (S[I])
		{
			MW = 0;
			PR = -1;
			if (S[I] == '%')
			{
				I++;
				while (S[I] >= '0' && S[I] <= '9')
					MW = MW * 10 + S[I++] - 48;
				if (S[I] == '.')
				{
					I++;
					PR++;
					while (S[I] >= '0' && S[I] <= '9')
						PR = PR * 10 + S[I++] - 48;
				}
				if (S[I] == 'd')
					print_d(f);
				if (S[I] == 'x')
					print_x(f);
				if (S[I] == 's')
					print_s(f);
			}
			ft_putchar(S[I++]);
		}
		va_end(ARG);
	}
	return (g_ret);
}
