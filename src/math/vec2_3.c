/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math/vec2_3.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gel/math/vector.h>

inline void		vec2clamp(t_vec2 a, float bottom, float top)
{
	a[0] = clampf(a[0], bottom, top);
	a[1] = clampf(a[1], bottom, top);
}

inline void		vec2neg(t_vec2 a)
{
	a[0] = -a[0];
	a[1] = -a[1];
}

inline void		vec2abs(t_vec2 a)
{
	a[0] = fabsf(a[0]);
	a[1] = fabsf(a[1]);
}

inline void		vec2norm(t_vec2 a)
{
	vec2scale(a, 1.f / vec2len(a));
}

inline void		vec2floor(t_vec2 a)
{
	a[0] = floorf(a[0]);
	a[1] = floorf(a[1]);
}
