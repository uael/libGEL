/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math/vec2_1.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gel/math/vector.h>

inline void		vec2cpy(t_vec2 a, t_vec2 const b)
{
	a[0] = b[0];
	a[1] = b[1];
}

inline void		vec2add(t_vec2 a, t_vec2 const b)
{
	a[0] += b[0];
	a[1] += b[1];
}

inline void		vec2sub(t_vec2 a, t_vec2 const b)
{
	a[0] -= b[0];
	a[1] -= b[1];
}

inline void		vec2mul(t_vec2 a, t_vec2 const b)
{
	a[0] *= b[0];
	a[1] *= b[1];
}

inline void		vec2div(t_vec2 a, float fac)
{
	a[0] *= fac;
	a[1] *= fac;
}
