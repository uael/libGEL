/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math/quat_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gel/math/quat.h>

inline void		quatconj(t_quat a)
{
	a[0] = -a[0];
	a[1] = -a[1];
	a[2] = -a[2];
}

inline void		quatscale(t_quat a, float fac)
{
	a[0] *= fac;
	a[1] *= fac;
	a[2] *= fac;
	a[3] *= fac;
}

inline void		quatrot(t_quat a, t_vec3 axis, float deg)
{
	t_vec3 v;

	vec3cpy(v, axis);
	vec3scale(v, sinf(deg / 2));
	a[0] = v[0];
	a[1] = v[1];
	a[2] = v[2];
	a[3] = cosf(deg / 2);
}
