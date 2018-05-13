#ifndef GEL_FRUSTRUM_H
# define GEL_FRUSTRUM_H

# include "gel/geometry/box.h"
# include "gel/math/vector.h"
# include "gel/math/matrix.h"

typedef struct  s_frustrum
{
	t_vec3      ntr;
	t_vec3      ntl;
	t_vec3      nbr;
	t_vec3      nbl;
	t_vec3      ftr;
	t_vec3      ftl;
	t_vec3      fbr;
	t_vec3      fbl;
}               t_frustum;

t_frustum       frustum_new(t_vec3 ntr, t_vec3 ntl, t_vec3 nbr, t_vec3 nbl, t_vec3 ftr, t_vec3 ftl, t_vec3 fbr, t_vec3 fbl);
t_frustum       frustum_new_clipbox();
t_frustum       frustum_new_camera(t_mat4 view, t_mat4 proj);
t_frustum       frustum_slice(t_frustum f, float start, float end);
t_frustum       frustum_transform(t_frustum f, t_mat4 m);
t_frustum       frustum_translate(t_frustum f, t_vec3 v);

t_vec3          frustum_center(t_frustum f);
t_vec3          frustum_maximums(t_frustum f);
t_vec3          frustum_minimums(t_frustum f);

t_box           frustum_box(t_frustum f);

bool            frustum_outside_box(t_frustum f, t_box b);

#endif
