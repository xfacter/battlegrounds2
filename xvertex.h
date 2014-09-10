#ifndef __X_VERTEX_H__
#define __X_VERTEX_H__

#include <psptypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Vertex */

int texture_bits(int vtype);

int color_bits(int vtype);

int normal_bits(int vtype);

int vertex_bits(int vtype);

int texture_offset(int vtype);

int color_offset(int vtype);

int normal_offset(int vtype);

int vertex_offset(int vtype);

int total_offset(int vtype);

void xVertSoftNormals(int vtype, int count, void* vertices);

void xVertHardNormals(int prim, int vtype, int count, void* vertices);

void xVertTranslate(int vtype, int count, void* vertices, ScePspFVector3* translate);

void xVertRotateX(int vtype, int count, void* vertices, float radians);

void xVertRotateY(int vtype, int count, void* vertices, float radians);

void xVertRotateZ(int vtype, int count, void* vertices, float radians);

void* xVertNewTranslated(int vtype, int count, void* vertices, ScePspFVector3* translate);

void* xVertNewRotatedX(int vtype, int count, void* vertices, float radians);

void* xVertNewRotatedY(int vtype, int count, void* vertices, float radians);

void* xVertNewRotatedZ(int vtype, int count, void* vertices, float radians);

#ifdef __cplusplus
}
#endif

#endif
