#include <stdio.h>
#include <stdlib.h>

static size_t	ft_word_count(const char *s, char c)
{
	size_t	num;

	num = 0;
	while (*s)
	{
		if (*s != c)
		{
			++num;
			while (*s && *s != c)
				++s;
		}
		else
			++s;
	}
	return (num);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char *)malloc((sizeof(char)) * len + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
	return (str);
}

char	**ft_split(const char *s, char c)
{
	char	**ret;
	size_t	i;
	size_t	len;

	if (!s)
		return (0);
	i = 0;
	ret = malloc(sizeof(char *) * (ft_word_count(s, c) + 1));
	if (!ret)
		return (0);
	while (*s)
	{
		if (*s == c)
		{
			s++;
			continue ;
		}
		len = 0;
		while (s[len] && s[len] != c)
			len++;
		ret[i++] = ft_substr(s, 0, len);
		s += len;
	}
	ret[i] = 0;
	return (ret);
}



int main()
{
	char *str;
	int i;
	
	i = 0;
	str = malloc(sizeof(char) * (25));
	free(str);
	str = "ahmet mehmet cemil";
	char **str_1 = ft_split(str, ' ');
	while (str_1[i])
	{
		printf("%s \n" , str_1[i]);
		i++;
	}
	i = 0;
	/*while (str_1[i])
		free(str_1[i++]);
	free(str_1);*/
}