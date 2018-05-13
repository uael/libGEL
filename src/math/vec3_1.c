/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math/vec3_1.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gel/math/vector.h>

inline void		vec3cpy(t_vec3 a, t_vec3 const b)
{
	a[0] = b[0];
	a[1] = b[1];
	a[2] = b[2];
}

inline void		vec3add(t_vec3 a, t_vec3 const b)
{
	a[0] += b[0];
	a[1] += b[1];
	a[2] += b[2];
}

inline void		vec3sub(t_vec3 a, t_vec3 const b)
{
	a[0] -= b[0];
	a[1] -= b[1];
	a[2] -= b[2];
}

inline void		vec3mul(t_vec3 a, t_vec3 const b)
{
	a[0] *= b[0];
	a[1] *= b[1];
	a[2] *= b[2];
}

inline void		vec3div(t_vec3 a, float fac)
{
	a[0] *= fac;
	a[1] *= fac;
	a[2] *= fac;
}
