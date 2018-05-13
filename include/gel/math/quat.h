/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gel/math/quat.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEL_MATH_QUAT_H
# define GEL_MATH_QUAT_H

# include "vector.h"

typedef float	t_quat[4];

extern void		quatcpy(t_quat a, t_quat const b);
extern void		quatid(t_quat a);
extern void		quatadd(t_quat a, t_quat const b);
extern void		quatsub(t_quat a, t_quat const b);
extern void		quatmul(t_quat a, t_quat const b);
extern void		quatconj(t_quat a);
extern void		quatscale(t_quat a, float fac);
extern void		quatrot(t_quat a, t_vec3 axis, float deg);

#endif
