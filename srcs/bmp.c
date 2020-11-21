/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:45:10 by zqadiri           #+#    #+#             */
/*   Updated: 2020/11/21 13:32:51 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Cub3d.h"

int     bit_map_file_headers(t_index *m, int fd, int file_size)
{
    // Bitshifting is simply moving those sequences of 1s and 0s left or right
    char HEADER[54];
    int info;
    
    ft_bzero(HEADER, 54);
    HEADER[0]  = (unsigned int)('B');
    HEADER[1]  = (unsigned int)('M');
    HEADER[2]  = (unsigned int)(file_size);
    HEADER[3]  = (unsigned int)(file_size >> 8);
    HEADER[4]  = (unsigned int)(file_size >> 16);
    HEADER[5]  = (unsigned int)(file_size >> 24);
    HEADER[10] = (54);
    HEADER[14] = (40);
    info = m->el.res_x;
    HEADER[18] = (unsigned int)(info);
    HEADER[19] = (unsigned int)(info >> 8);
    HEADER[20] = (unsigned int)(info >> 16);
    HEADER[21] = (unsigned int)(info >> 24);
    info = -m->el.res_y; // the first pixel is the last one 
    HEADER[22] = (unsigned int)(info);
    HEADER[23] = (unsigned int)(info >> 8);
    HEADER[24] = (unsigned int)(info >> 16);
    HEADER[25] = (unsigned int)(info >> 24);
    HEADER[26] = (1);
    HEADER[28] = (32);
    write(fd, HEADER, 54);
    return(1);
}

int     write_info(t_index *m, int fd)
{
    char *data;
    
    data = (char *)m->img.addr;
    if(write(fd, data, 4 * m->el.res_x * m->el.res_y) < 0)
        return (-1);
    return (1);
}

int		screen_shot(t_index *m)
{
	int	fd;
    int file_size;

	if ((fd = open("screenshot.bmp", O_CREAT | O_RDWR | S_IRWXU)) < 0)
		return (exit_all(m));
    file_size = 14 + 40 * (m->el.res_x * m->el.res_y) * 4;//NumColors bytes
    if (bit_map_file_headers(m, fd, file_size) < 0)
        return (-1);
    if (write_info(m ,fd) < 0)
        return (-1);
    exit_all(m);
    return(1);
}