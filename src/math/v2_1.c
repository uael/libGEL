/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math/v2_1.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gel/math/vector.h>

t_v2	v2(float x, float y)
{
	t_v2 v;

	v.x = x;
	v.y = y;
	return (v);
}

t_v2	v2zero(void)
{
	return v2(0, 0);
}

t_v2	v2one(void)
{
	return v2(1, 1);
}

t_v2	v2add(t_v2 v1, t_v2 v2)
{
	t_v2 v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	return (v);
}

t_v2	v2sub(t_v2 v1, t_v2 v2)
{
	t_v2 v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	return (v);
}
