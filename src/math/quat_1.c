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

inline void		quatid(t_quat a)
{
	a[0] = 0;
	a[1] = 0;
	a[2] = 0;
	a[3] = 1;
}

inline void		quatcpy(t_quat a, t_quat const b)
{
	a[0] = b[0];
	a[1] = b[1];
	a[2] = b[2];
	a[3] = b[3];
}

inline void		quatadd(t_quat a, t_quat const b)
{
	a[0] += b[0];
	a[1] += b[1];
	a[2] += b[2];
	a[3] += b[3];
}

inline void		quatsub(t_quat a, t_quat const b)
{
	a[0] -= b[0];
	a[1] -= b[1];
	a[2] -= b[2];
	a[3] -= b[3];
}

inline void		quatmul(t_quat a, t_quat const b)
{
	a[0] *= b[0];
	a[1] *= b[1];
	a[2] *= b[2];
	a[3] *= b[3];
}
