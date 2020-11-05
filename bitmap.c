/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matvivan <matvivan@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:29:14 by matvivan          #+#    #+#             */
/*   Updated: 2020/11/01 20:16:13 by matvivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
**	File Header + Info Header:
**	Total 54 bytes, but used 56 bytes and then shifted 2 Bytes
**	(56 / 4 = 14 integer array size);
**	All fields set to zero value (0) by ft_memset.
**	header[0] - [Field 1] File format - "BM".
**	header[1] - [Field 2] File size = bitmap data + header size.
**	header[3] - [Field 5] Header size (Data offset) - 54 bytes.
**	header[4] - [Field 6] Info Header size - 40 bytes.
**	header[5] - [Field 7] Image width.
**	header[6] - [Field 8] Image height inverted (BMP stored pxls bottom to up).
**	header[7] - [Field 9, 10] 1 planes, 32 bpp (both default).
**	Rest fields value remaining default.
**	When writing have to be shifted since first two bytes unused
**	("BM" stored in 2 B of total 4 B int size).
*/

void		save_bmp(t_mlx *ptr)
{
	int		fd;
	int		header[14];
	int		file_size;

	fd = open("./image.bmp", O_RDWR | O_CREAT, 0644);
	if (fd > 0)
	{
		file_size = ptr->width * ptr->height * 4;
		ft_memset(header, '\0', 56);
		header[0] = 0x4D420000;
		header[1] = file_size + 54;
		header[3] = 54;
		header[4] = 40;
		header[5] = ptr->width;
		header[6] = -ptr->height;
		header[7] = 0x00200001;
		write(fd, (char *)header + 2, 54);
		write(fd, (ptr->cam->img_ptr)[1], file_size);
	}
	else
		write(1, "Error due to FD\n", 16);
	close(fd);
}
