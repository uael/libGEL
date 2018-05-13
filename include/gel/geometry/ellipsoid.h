#ifndef GEL_ELLIPSOID_H
# define GEL_ELLIPSOID_H

# include "gel/math/vector.h"
# include "gel/math/matrice.h"
# include "gel/geometry/sphere.h"

typedef struct s_ellipsoid
{
    t_vec3 center;
    t_vec3 radiuses;
}               t_ellipsoid;

t_ellipsoid ellipsoid_new(t_vec3 center, t_vec3 radiuses);
t_ellipsoid ellipsoid_transform(t_ellipsoid e, t_mat4 m);
t_ellipsoid ellipsoid_of_sphere(t_sphere s);

t_mat3 ellipsoid_space(t_ellipsoid e);
t_mat3 ellipsoid_inv_space(t_ellipsoid e);

#endif
