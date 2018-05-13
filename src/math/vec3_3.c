/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math/vec3_3.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gel/math/vector.h>

inline void		vec3clamp(t_vec3 a, float bottom, float top)
{
	a[0] = clampf(a[0], bottom, top);
	a[1] = clampf(a[1], bottom, top);
	a[2] = clampf(a[2], bottom, top);
}

inline void		vec3neg(t_vec3 a)
{
	a[0] = -a[0];
	a[1] = -a[1];
	a[2] = -a[2];
}

inline void		vec3abs(t_vec3 a)
{
	a[0] = fabsf(a[0]);
	a[1] = fabsf(a[1]);
	a[2] = fabsf(a[2]);
}

inline void		vec3norm(t_vec3 a)
{
	vec3scale(a, 1.f / vec3len(a));
}

inline void		vec3floor(t_vec3 a)
{
	a[0] = floorf(a[0]);
	a[1] = floorf(a[1]);
	a[2] = floorf(a[2]);
}
