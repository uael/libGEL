#ifndef GEL_MODEL_H
#define GEL_MODEL_H

# include "gel/math/vector.h"
# include "gel/math/matrix.h"
# include "gel/geometry/mesh.h"

typedef struct s_model
{
    int num_meshes;
    t_mesh** meshes;
} t_model;

t_model* model_new();
void model_delete(t_model* m);

void model_generate_normals(t_model* m);
void model_generate_tangents(t_model* m);
void model_generate_orthagonal_tangents(t_model* m);
void model_generate_texcoords_cylinder(t_model* m);

void model_print(t_model* m);
float model_surface_area(t_model* m);

void model_transform(t_model* m, t_mat4 transform);
void model_translate(t_model* m, t_vec3 translation);
void model_scale(t_model* m, float scale);

#endif
