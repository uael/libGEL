/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math/vec3_2.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gel/math/vector.h>

inline void		vec3pow(t_vec3 a, float exp)
{
	a[0] = powf(a[0], exp);
	a[1] = powf(a[1], exp);
	a[2] = powf(a[2], exp);
}

inline void		vec3min(t_vec3 a, float x)
{
	a[0] = fminf(a[0], x);
	a[1] = fminf(a[1], x);
	a[2] = fminf(a[2], x);
}

inline void		vec3max(t_vec3 a, float x)
{
	a[0] = fmaxf(a[0], x);
	a[1] = fmaxf(a[1], x);
	a[2] = fmaxf(a[2], x);
}

inline void		vec3fmod(t_vec3 a, float val)
{
	a[0] = fmodf(a[0], val);
	a[1] = fmodf(a[1], val);
	a[2] = fmodf(a[2], val);
}

inline void		vec3scale(t_vec3 a, float fac)
{
	a[0] *= fac;
	a[1] *= fac;
	a[2] *= fac;
}
