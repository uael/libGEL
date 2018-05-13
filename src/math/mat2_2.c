/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math/mat2_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gel/math/matrix.h>

inline void		mat2zero(t_mat2 a)
{
	a[0][0] = 0.0f;
	a[0][1] = 0.0f;
	a[1][0] = 0.0f;
	a[1][1] = 0.0f;
}

inline void		mat2inv(t_mat2 a)
{
	float fac;
	float i;

	fac = 1.0f / mat2det(a);
	i = a[0][0];
	a[0][0] = fac * a[1][1];
	a[0][1] = fac * -a[0][1];
	a[1][0] = fac * -a[1][0];
	a[1][1] = fac * i;
}

inline void		mat2tra(t_mat2 a)
{
	float i;

	i = a[0][1];
	a[0][1] = a[1][0];
	a[1][0] = i;
}

inline float	mat2det(t_mat2 const a)
{
	return (a[0][0] * a[1][1] - a[0][1] * a[1][0]);
}
