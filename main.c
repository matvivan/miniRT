/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matvivan <matvivan@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 19:13:40 by matvivan          #+#    #+#             */
/*   Updated: 2020/11/04 22:05:15 by matvivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int				clear_exit(t_mlx *ptr)
{
	int			i;

	i = 0;
	while (ptr->cam_array[i])
	{
		mlx_destroy_image(ptr->mlx, ptr->cam[i].img_ptr);
		free(ptr->cam_array[i]->depth);
		free(ptr->cam_array[i]);
		++i;
	}
	free(ptr->cam_array);
	i = 0;
	while (ptr->obj[i])
		free(ptr->obj[i++]);
	free(ptr->obj);	
	mlx_destroy_window(ptr->mlx, ptr->win);
	system("leaks miniRT");
	exit(0);
	return (0);
}

void			print_point(char *name, t_point a)
{
	printf("%s: x=% .0f, y=% .0f, z=% .0f\n", name, a.x, a.y, a.z);
}

void			print_vector(char *name, t_vector a)
{
	printf("%s: x=% .0f, y=% .0f, z=% .0f\n", name, a.x, a.y, a.z);
}

void			print_matrix(char *name, t_matrix m)
{
	printf("\t%s\n", name);
	print_vector("\trg", m.rg);
	print_vector("\tup", m.up);
	print_vector("\tfw", m.fw);
}

void			print_stat(t_mlx *ptr, t_vector ray)
{
	printf("ray length:  %d\n", (int)sqrt(dot(ray, ray)));
	print_point("cam origin", ptr->cam->origin);
	print_matrix("cam_to_world", matrix_init(ptr->cam));
	printf("fov: %d degree\n", ptr->cam->fov);
	print_vector("ray", ray);
	print_vector("rayWorld", vector_matrix_prod(ray, matrix_init(ptr->cam)));
//	printf("%d\n", (uint32_t)(0xFFFFFF * 0.2));
}

void			rotate(double *hor, double *ver, double radian)
{
	double		old_hor;
	double		old_ver;

	old_hor = *hor;
	old_ver = *ver;
	*hor = old_hor * cos(radian) + old_ver * -sin(radian);
	*ver = old_hor * sin(radian) + old_ver *  cos(radian);
}

int				key_hook(int key, t_mlx *ptr)
{
	if (key == 53)
		clear_exit(ptr);
	if (key == 126)
		ptr->cam->origin = add(ptr->cam->origin, ptr->cam->direct);
	if (key == 125)
		ptr->cam->origin = sub(ptr->cam->origin, ptr->cam->direct);
	if (key == 123)
		rotate(&ptr->cam->direct.z, &ptr->cam->direct.x, 18 * M_PI / 180);
	if (key == 124)
		rotate(&ptr->cam->direct.z, &ptr->cam->direct.x, -18 * M_PI / 180);
	if (key == 27 && ptr->cam->fov > 5)
		ptr->cam->fov -= 5;
	if (key == 24 && ptr->cam->fov < 175)
		ptr->cam->fov += 5;
//	pallette(ptr->cam->canvas, ptr->width * ptr->height);
	ft_memset(ptr->cam->canvas, 0, ptr->width * ptr->height * sizeof(int));
	mlx_clear_window(ptr->mlx, ptr->win);
	set_camera(ptr, ptr->cam, ptr->obj);
	print_stat(ptr, ptr->cam->direct);
	printf("key: %d\n", key);
	return (0);
}

t_point			point_init(double x, double y, double z)
{
	t_point		ray;

	ray.x = x;
	ray.y = y;
	ray.z = z;
	return (ray);
}

t_vector		vector_init(double x, double y, double z)
{
	t_vector	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

int				main(int ac, char **av)
{
	t_mlx		*ptr;

	ptr = (t_mlx *)malloc(sizeof(t_mlx));
	ptr->mlx = mlx_init();
	/* obtain rt file */
	ptr->width = 1024;
	ptr->height = 512;
	/* Camera array */
	ptr->cam_array = malloc(2 * sizeof(t_camera *));
	ptr->cam_array[1] = NULL;
		ptr->cam_array[0] = (t_camera *)malloc(sizeof(t_camera));
		ptr->cam_array[0]->w = ptr->width;
		ptr->cam_array[0]->h = ptr->height;
		ptr->cam_array[0]->origin = point_init(0, 0, 0);
		ptr->cam_array[0]->direct = vector_init(0, 0, 1);
		ptr->cam_array[0]->fov = 90;
		ptr->cam_array[0]->img_ptr = mlx_new_image(ptr->mlx, ptr->width, ptr->height);
		ptr->cam_array[0]->canvas = ptr->cam_array[0]->img_ptr[1];
		ptr->cam_array[0]->depth = malloc(ptr->width * ptr->height * sizeof(double));
	/* Current camera */
	ptr->cam = ptr->cam_array[0];
	/* Object array */
	ptr->obj = malloc(4 * sizeof(void *));
	ptr->obj[3] = NULL;
		ptr->obj[0] = (t_obj *)sphere_init(point_init(2, 0, 20), 3, 0xEE00EE);
		ptr->obj[1] = (t_obj *)sphere_init(point_init(-1, 0, 20), 2, 0x00EEEE);
		ptr->obj[2] = (t_obj *)sphere_init(point_init(0, -1003, 20), 1000, 0xEEEE00);
	/* LIGHT */
	ptr->light = malloc(4 * sizeof(t_light *));
	ptr->light[3] = NULL;
		/* Ambient light */
		ptr->light[0] = malloc(sizeof(t_light));
		ptr->light[0]->argb = 0xFFFFFF;
		ptr->light[0]->ratio = 0.2;
		/* Artificial light 1 */
		ptr->light[1] = malloc(sizeof(t_light));
		ptr->light[1]->argb = 0xFFFFFF;
		ptr->light[1]->ratio = 0.6;
		ptr->light[1]->c = point_init(10, 10, 18);
		/* Artificial light 2 */
		ptr->light[2] = malloc(sizeof(t_light));
		ptr->light[2]->argb = 0xFFFFFF;
		ptr->light[2]->ratio = 0.6;
		ptr->light[2]->c = point_init(-10, 10, 22);
	/* rt file obtained */
	if (ptr->mlx)
	{
		ptr->win = mlx_new_window(ptr->mlx, ptr->width, ptr->height, "miniRT");
		if (ptr->win)
		{
			set_camera(ptr, ptr->cam, ptr->obj);
			
			if (ac > 1 && ft_strequ(av[1], "--save"))
			{
				save_bmp(ptr);
				clear_exit(ptr);
			}
			/* set hooks */
			mlx_key_hook(ptr->win, &key_hook, ptr);
			mlx_hook(ptr->win, 17, 0, &clear_exit, ptr);
			mlx_loop(ptr->mlx);
		}
	}
	return (0);
}
