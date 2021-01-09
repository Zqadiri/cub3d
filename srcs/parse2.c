/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 18:00:46 by zqadiri           #+#    #+#             */
/*   Updated: 2021/01/09 19:35:43 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub.h"

int		digit(char *c)
{
	int i;

	i = 0;
	while (c[i] != '\0' && !ft_isalpha(c[i]))
	{
		if (c[i] >= '0' && c[i] <= '9')
			return (1);
		i++;
	}
	return (0);
}

int		is_white_space(char c)
{
    if (c == ' ' || c == '\t')
        return (1);
	return (0);
}


int		is_empty(char *s)
{
	int i;

	if (!s)
		return (1);
	i = 0;
	if (s[0] == '\0')
		return (1);
	while (s[i] != '\0')
	{
		if (s[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int     check_line(char *s)
{
    int i;
    int no_digit;

    i = 0;
    no_digit = 0;
    if (digit(s))
        no_digit = 1;
    while (s[i])
    {
        if (is_white_space(s[i]) && !no_digit)
            return (-1);
        else
            i++;
    }
    return (1);
}


int     parse_map2(int fd)
{
    int not_empty;
    int ret;
    char *line;
    char *map_string;
    int last;

    line = NULL;
    ret = 1;
    not_empty = 0;
    map_string = "";
    last = 0;
    while (ret)
    {
        // printf ("<%s>\n", map_string);
        ret = get_next_line(fd, &line);
        if (last && is_empty(line))
        {
            write(1, "error1\n", 7);
            return (-1);
        }
        if ((not_empty && line[0] != '\n'))
        {
            write(1, "error2\n", 7);
            return (-1);
        } 
        if (is_empty(line) && digit(map_string))
            last = 1;
        if (check_line(line) < 0)
            not_empty = 1;
        else
        {
            map_string = ft_strjoin(map_string, line);
            map_string = ft_strjoin(map_string, "\n");
        }
    }
    map_string = ft_strjoin(map_string, line);
    map_string = ft_strjoin(map_string, "\0");
    printf("|%s|\n", map_string);
    return(1);
}

int     main(int argc, char **argv)
{
    
    int fd;
    if(argc == 2)
    {
        fd = open(argv[1], O_RDONLY);
        parse_map2 (fd);
        close (fd);
    }
    return (1);
}

// int			parse_map(int fd, t_index *m)
// {
// 	char	*pfree;

// 	while (is_empty(m->parse.line) && m->parse.ret != 0)
// 	{
// 		free(m->parse.line);
// 		m->parse.ret = get_next_line(fd, &m->parse.line);
// 	}
// 	m->parse.map_string = ft_strjoin(m->parse.map_string, m->parse.line);
// 	pfree = m->parse.map_string;
// 	m->parse.map_string = ft_strjoin(m->parse.map_string, "\n");
// 	clear(pfree, m->parse.line);
// 	while (get_next_line(fd, &m->parse.line))
// 	{
// 		(is_empty(m->parse.line) && m->parse.end) ? write_error_one(m) : 1;
// 		if (is_empty(m->parse.line))
// 		{
// 			m->parse.end = 1;
// 			free(m->parse.line);
// 			continue;
// 		}
// 		join_line(m, m->parse.line, pfree, 1);
// 	}
// 	pfree = m->parse.map_string;
// 	join_line(m, m->parse.line, pfree, 0);
// 	return (1);
// }