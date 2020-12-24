#include "get_next_line.h"

void	*ft_calloc(size_t n, size_t size)
{
	size_t	i;
	char	*str;

	i = 0;
	if(!(str = malloc(n * size)))
		return (NULL);
	while (i < n * size)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}

int		line_exist(char *storage)
{
	int i;

	i = 0;
	while (storage[i])
	{
		if (storage[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int		ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	if (!(s = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	while (s1[i])
		s[j++] = s1[i++];
	i = 0;
	while (s2[i])
		s[j++] = s2[i++];
	s[j] = '\0';
	return (s);
}

int		read_fd(char **storage)
{
	int		ret;
	char	*buf;
	char	*tmp;

	if (!(buf = malloc(BUFFER_SIZE + 1)))
		return (-1);
	while (line_exist(*storage) == -1)
	{
		ret = read(0, buf, BUFFER_SIZE);
		if (ret == -1 || ret == 0)
			break ;
		buf[ret] = '\0';
		tmp = *storage;
		*storage = ft_strjoin(*storage, buf);
		free(tmp);
		tmp = NULL;
	}
	free(buf);
	return (ret);
}

char	*fill_line(char *storage)
{
	char	*line;
	int		i;

	if (!(line = ft_calloc(line_exist(storage) + 1, 1)))
		return (NULL);
	i = 0;
	while (storage[i] != '\n')
	{
		line[i] = storage[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

int		get_next_line(char **line)
{
	int			rd;
	static char	*storage;
	char		*tmp;

	if (!line)
		return (-1);
	if (!storage && !(storage = ft_calloc(1, 1)))
		return (-1);
	if (line_exist(storage) == -1)
	{
		rd = read_fd(&storage);
		if (rd == -1)
			return (-1);
		if (rd == 0)
		{
			*line = ft_strjoin(storage, "");
			free(storage);
			storage = NULL;
			return (0);
		}
	}
	*line = fill_line(storage);
	tmp = storage;
	storage = ft_strjoin(storage + line_exist(storage) + 1, "");
	free(tmp);
	tmp = NULL;
	return (1);
}
