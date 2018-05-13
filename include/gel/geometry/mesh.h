#ifndef GEL_MESH_H
#define GEL_MESH_H

# include "gel/math/vector.h"
# include "gel/math/matrice.h"
# include "gel/geometry/vertex.h"
# include "gel/geometry/sphere.h"

typedef struct s_mesh
{
    int num_verts;
    int num_triangles;
    t_vertex* verticies;
    uint32_t* triangles;
} t_mesh;

t_mesh* mesh_new();
void mesh_delete(t_mesh* m);

void mesh_generate_normals(t_mesh* m);
void mesh_generate_tangents(t_mesh* m);
void mesh_generate_orthagonal_tangents(t_mesh* m);
void mesh_generate_texcoords_cylinder(t_mesh* m);

void mesh_print(t_mesh* m);
float mesh_surface_area(t_mesh* m);

void mesh_transform(t_mesh* m, t_mat4 transform);
void mesh_translate(t_mesh* m, t_vec3 translation);
void mesh_scale(t_mesh* m, float scale);

t_sphere mesh_bounding_sphere(t_mesh* m);

#endif
