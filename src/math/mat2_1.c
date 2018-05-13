/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math/mat2_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gel/math/matrix.h>

inline void		mat2cpy(t_mat2 a, t_mat2 const b)
{
	a[0][0] = b[0][0];
	a[0][1] = b[0][1];
	a[1][0] = b[1][0];
	a[1][1] = b[1][1];
}

inline void		mat2mul(t_mat2 a, t_mat2 const b)
{
	float i;

	i = a[0][0];
	a[0][0] = i * b[0][0] + a[0][1] * b[1][0];
	a[0][1] = i * b[0][1] + a[0][1] * b[1][1];
	i = a[1][0];
	a[1][0] = i * b[0][0] + a[1][1] * b[1][0];
	a[1][1] = i * b[0][1] + a[1][1] * b[1][1];
}

inline void		mat2mulv(t_vec2 a, t_mat2 const b)
{
	float i;

	i = a[0];
	a[0] = i * b[0][0] + a[1] * b[0][1];
	a[1] = i * b[1][0] + a[1] * b[1][1];
}

inline void		mat2rot(t_mat2 a, float deg)
{
	a[0][0] = cosf(deg);
	a[0][1] = -sinf(deg);
	a[1][0] = sinf(deg);
	a[1][1] = cosf(deg);
}

inline void		mat2id(t_mat2 a)
{
	a[0][0] = 1.0f;
	a[0][1] = 0.0f;
	a[1][0] = 0.0f;
	a[1][1] = 1.0f;
}
