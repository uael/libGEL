/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math/vec4_3.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gel/math/vector.h>

inline void		vec4clamp(t_vec4 a, float bottom, float top)
{
	a[0] = clampf(a[0], bottom, top);
	a[1] = clampf(a[1], bottom, top);
	a[2] = clampf(a[2], bottom, top);
	a[3] = clampf(a[3], bottom, top);
}

inline void		vec4neg(t_vec4 a)
{
	a[0] = -a[0];
	a[1] = -a[1];
	a[2] = -a[2];
	a[3] = -a[3];
}

inline void		vec4abs(t_vec4 a)
{
	a[0] = fabsf(a[0]);
	a[1] = fabsf(a[1]);
	a[2] = fabsf(a[2]);
	a[3] = fabsf(a[3]);
}

inline void		vec4norm(t_vec4 a)
{
	vec4scale(a, 1.f / vec4len(a));
}

inline void		vec4floor(t_vec4 a)
{
	a[0] = floorf(a[0]);
	a[1] = floorf(a[1]);
	a[2] = floorf(a[2]);
	a[3] = floorf(a[3]);
}
