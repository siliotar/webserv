#include "utils.hpp"

int		ft_strlen(const char *str)
{
	int i;

	i = 0;
	if (str)
		while (str[i] != 0)
			i++;
	return (i);
}

char	*find_new_line(char *buff)
{
	int i;

	i = -1;
	while (buff[++i] != 0)
		if (buff[i] == '\n')
		{
			buff[i] = '\0';
			return (ft_strdup(&buff[i + 1]));
		}
	return (0);
}

char	*ft_strjoin(const char *str1, const char *str2)
{
	int		i;
	int		j;
	char	*str;

	i = ft_strlen(str1);
	j = ft_strlen(str2);
	if (!(str = (char *)malloc(i + j + 1)))
		return (0);
	i = 0;
	j = 0;
	if (str1 != 0 && (i = -1))
		while (str1[++i] != 0)
			str[i] = str1[i];
	if (str2 != 0 && (j = -1))
		while (str2[++j] != 0)
			str[i + j] = str2[j];
	str[i + j] = 0;
	return (str);
}

char	*ft_strdup(const char *str)
{
	char	*str_cpy;
	size_t	i;

	if (str == 0)
		return (0);
	i = ft_strlen(str);
	if (!(str_cpy = (char *)malloc(i + 1)))
		exit(0);
	str_cpy[i] = 0;
	i = 0;
	while (*str != 0)
	{
		str_cpy[i] = *str;
		i++;
		str++;
	}
	return (str_cpy);
}

static void	is_str(char **temp, char **after_n, char **line, char **str)
{
	*temp = *after_n;
	*after_n = find_new_line(*str);
	if (*temp)
		free(*temp);
	*temp = *line;
	*line = ft_strjoin(*line, *str);
	if (*temp)
		free(*temp);
	free(*str);
	*str = ft_strdup(*after_n);
}

static int	some_read(char **buff, char **line, char **after_n, int fd)
{
	int		count;
	char	*temp;

	count = 1;
	while (count > 0)
	{
		count = read(fd, *buff, 100);
		(*buff)[count] = 0;
		temp = *after_n;
		*after_n = find_new_line(*buff);
		if (temp)
			free(temp);
		temp = *line;
		*line = ft_strjoin(*line, *buff);
		if (temp)
			free(temp);
		if (*after_n != 0)
			break ;
	}
	return (count);
}

static int	some_func(char **str, char **after_n, char **buff, int count)
{
	free(*str);
	free(*buff);
	*str = ft_strdup(*after_n);
	if (*after_n)
		free(*after_n);
	if (*str == 0 && count == 0)
		return (0);
	if (*str == 0 && count != 0)
		return (-1);
	return (1);
}

int			c_get_next_line(int fd, char **line)
{
	static char	*str[1024];
	int			c;
	char		*after_n;
	char		*temp;
	char		*buff;

	buff = (char *)malloc(101);
	c = 1;
	if ((c = read(fd, &c, 0)) == -1 || fd < 0 || line == 0)
		return (-1);
	if ((*line = 0) && !str[fd])
		if (!(str[fd] = ft_strdup("")))
			return (-1);
	if (((after_n = 0) == 0) && str[fd] != 0 && *(str[fd]) != 0)
	{
		is_str(&temp, &after_n, line, &(str[fd]));
		if (after_n)
		{
			free(after_n);
			return (1);
		}
	}
	c = some_read(&buff, line, &after_n, fd);
	return (some_func(&str[fd], &after_n, &buff, c));
}