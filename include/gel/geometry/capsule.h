#ifndef GEL_CAPSULE_H
# define GEL_CAPSULE_H

# include "gel/math/vector.h"
# include "gel/math/matrix.h"
# include "gel/geometry/plane.h"

typedef struct s_capsule
{
    t_vec3 start;
    t_vec3 end;
    float radius;
}               t_capsule;

t_capsule capsule_new(t_vec3 start, t_vec3 end, float radius);
t_capsule capsule_transform(t_capsule c, t_mat4 m);

bool capsule_inside_plane(t_capsule c, t_plane p);
bool capsule_outside_plane(t_capsule c, t_plane p);
bool capsule_intersects_plane(t_capsule c, t_plane p);

#endif
