#include "cube.h"

/* Norminette moment */
void	get_route(char *line, char **route, bool *flag)
{
	free(*route);
	*route = ft_strdup(line);
	*flag = true;
}

/* Norminette moment */
void trim_and_dup(char **num)
{
    char*   aux;

    aux = NULL;
    aux = ft_strtrim(*num, " ,CF\t");
    free(*num);
    *num = ft_strdup(aux);
    free(aux);
}

/* We split the line in commas, after splitting it with
 * tabs and spaces. So two commas could be aside and we wouldnt
 * notice. This is a problem. This function solves it. It
 * essentially just counts how many commas are in the line. In
 * case its different from 2, we know its wrong, and in case it is
 * 2 and they are consecutive further controls will raise error.*/
int inspect_color_line(char *line)
{
    int     n_commas;

    n_commas = 0;
    while (*line)
    {
        if (*line == ',')
            ++n_commas;
        ++line;
    }
    if (n_commas != 2)
        return 0;
    else
        return 1;
}

int ft_matrixlen(char **mat)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (mat[i])
    {
        while (mat[i][j] <= '9' && mat[i][j] >= '0')
            j++;
        if (mat[i][j] != '\0')
            return -1;
        j = 0;
        i++;
    }
    return i;
}

void    position_after_F_or_C(char **line)
{
    char*   aux;

    aux = ft_strchr(*line, 'F');
    if (aux != NULL)
    {
        *line = aux;
        *line = *line + 1;
        return ;
    }
    aux = ft_strchr(*line, 'C');
    if (aux != NULL)
    {
        *line = aux;
        *line = *line + 1;
        return;
    }
    else
        return ;
}