/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:08:42 by zqadiri           #+#    #+#             */
/*   Updated: 2020/11/30 11:11:40 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int         file_header(t_index *m, int fd, int file_size, int info)
{
    char    header[54];

    ft_bzero(header, 54);
    header[0] = (unsigned int)('B');
    header[1] = (unsigned int)('M');
    header[2] = (unsigned int)(file_size);
    header[3] = (unsigned int)(file_size >> 8);
    header[4] = (unsigned int)(file_size >> 16);
    header[5] = (unsigned int)(file_size >> 24);
    header[10] = (54);
    header[14] = (40);
    header[18] = (unsigned int)(info);
    header[19] = (unsigned int)(info >> 8);
    header[20] = (unsigned int)(info >> 16);
    header[21] = (unsigned int)(info >> 24);
    info = -m->el.res_y;
    header[22] = (unsigned int)(info);
    header[23] = (unsigned int)(info >> 8);
    header[24] = (unsigned int)(info >> 16);
    header[25] = (unsigned int)(info >> 24);
    header[26] = (1);
    header[28] = (32);
    write(fd, header, 54);
    return(1);
}

int         write_info(t_index *m, int fd)
{
    char    *data;

    data = (char *)m->img.addr;
    if (write(fd, data, (4 * m->el.res_x * m->el.res_y)) < 0)
        return (-1);
    return (1);
}

int         screen_shot(t_index *m)
{
    int     fd;
    int     file_size;
    int     info;

    info = m->el.res_x;
    file_size = 14 + 40 * (m->el.res_x * m->el.res_y) * 4;
    if ((fd = open("screenshot.bmp", O_CREAT | O_RDWR | S_IRWXU)) < 0)
        return (exit_all(m));
    if (file_header(m, fd, file_size, info) < 0)
        return (exit_all(m));
    if (write_info(m, fd) < 0)
        return (exit_all(m));
    close(fd);
    exit_all(m);
    return (1);
}
