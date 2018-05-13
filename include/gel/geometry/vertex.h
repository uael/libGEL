#ifndef GEL_VERTEX_H
# define GEL_VERTEX_H

# include "gel/math/vector.h"

typedef struct s_vertex
{
    t_vec3 position;
    t_vec3 normal;
    t_vec3 tangent;
    t_vec3 binormal;
    t_vec4 color;
    t_vec2 uvs;
} t_vertex;

t_vertex vertex_new();
bool vertex_equal(t_vertex v1, t_vertex v2);
void vertex_print(t_vertex v);

#endif
