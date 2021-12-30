#include "cube.h"

static int	number_of_words(const char *s)
{
	int	i;

	i = 0;
	if (!s || !*s)
		return (0);
	if (*s != ' ' && *s != '\t')
		i = 1;
	while (*(s + 1))
	{
		if ((*s == ' ' || *s == '\t')
            && (*(s + 1) != ' ' && *(s + 1) != '\t')
            && *(s + 1) != '\0')
        {
                i++;
        }
		s++;
	}
	return (i);
}

static void	create_string_array(char **table, char const *s, int words)
{
	int	i;
	int	j;
	int	k;
	int	w;

	w = 0;
	i = 0;
	while (words-- > 0)
	{
		while ((s[i] == ' ' || s[i] == '\t'))
			i++;
		j = i;
		while ((s[i] != ' ' && s[i] != '\t') && s[i])
			i++;
		table[w] = (char *)malloc(sizeof(char) * (i - j + 1));
		k = 0;
		while (j < i)
			table[w][k++] = s[j++];
		table[w][k] = '\0';
		w++;
	}
	table[w] = NULL;
}

char	**split_line(char const *s)
{
	char			**table;
	unsigned int	words;

	if (!s)
		return (NULL);
	words = number_of_words(s);
	table = (char **)malloc(sizeof(char *) * (words + 1));
	if (!table)
		return (NULL);
	create_string_array(table, s, words);
	if (!table)
		return (NULL);
	return (table);
}