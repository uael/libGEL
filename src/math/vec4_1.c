/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math/vec4_1.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gel/math/vector.h>

inline void		vec4cpy(t_vec4 a, t_vec4 const b)
{
	a[0] = b[0];
	a[1] = b[1];
	a[2] = b[2];
	a[3] = b[3];
}

inline void		vec4add(t_vec4 a, t_vec4 const b)
{
	a[0] += b[0];
	a[1] += b[1];
	a[2] += b[2];
	a[3] += b[3];
}

inline void		vec4sub(t_vec4 a, t_vec4 const b)
{
	a[0] -= b[0];
	a[1] -= b[1];
	a[2] -= b[2];
	a[3] -= b[3];
}

inline void		vec4mul(t_vec4 a, t_vec4 const b)
{
	a[0] *= b[0];
	a[1] *= b[1];
	a[2] *= b[2];
	a[3] *= b[3];
}

inline void		vec4div(t_vec4 a, float fac)
{
	a[0] *= fac;
	a[1] *= fac;
	a[2] *= fac;
	a[3] *= fac;
}
