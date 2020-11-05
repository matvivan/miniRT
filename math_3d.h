/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_3d.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matvivan <matvivan@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 19:17:42 by matvivan          #+#    #+#             */
/*   Updated: 2020/11/04 20:35:04 by matvivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_3D_H
# define MATH_3D_H

# include "minirt.h"

typedef struct		s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

typedef t_vector	t_point;

double				dot(t_vector a, t_vector b);
t_vector			cross(t_vector a, t_vector b);
t_vector			mult(double t, t_vector v);
t_vector			normalize(t_vector v);
t_vector			sub(t_vector a, t_vector b);
t_vector			add(t_vector a, t_vector b);

#endif
