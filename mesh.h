#ifndef MESH_H
#define MESH_H

#include "hittable.h"
#include "hittable_list.h"
#include "triangle.h"
#include "../OFFReader.h"
#include <string>

class mesh : public hittable {
public:
    mesh(const std::string& filename, const point3& center, double scale = 1.0) {
        // Load the OFF file using the provided OFFReader
        OffModel* model = readOffFile(const_cast<char*>(filename.c_str()));
        
        if (!model) {
            std::cerr << "Failed to load OFF file: " << filename << std::endl;
            return;
        }

        // Calculate center of the model
        point3 model_center(
            (model->minX + model->maxX) / 2.0,
            (model->minY + model->maxY) / 2.0,
            (model->minZ + model->maxZ) / 2.0
        );

        // Scale factor to normalize the model to fit within the scene
        double normalizing_scale = scale / model->extent;

        // Create triangles from OFF polygons
        for (int i = 0; i < model->numberOfPolygons; i++) {
            Polygon polygon = model->polygons[i];
            
            // Currently only handling triangular faces
            if (polygon.noSides == 3) {
                // Get the three vertices of this triangle
                Vertex v0 = model->vertices[polygon.v[0]];
                Vertex v1 = model->vertices[polygon.v[1]];
                Vertex v2 = model->vertices[polygon.v[2]];

                // Transform vertices: center and scale
                point3 p0 = center + normalizing_scale * (point3(v0.x, v0.y, v0.z) - model_center);
                point3 p1 = center + normalizing_scale * (point3(v1.x, v1.y, v1.z) - model_center);
                point3 p2 = center + normalizing_scale * (point3(v2.x, v2.y, v2.z) - model_center);
                
                // Add triangle to the mesh
                triangles.add(make_shared<triangle>(p0, p1, p2));
            }
            else {
                // Simple triangulation for polygons with more than 3 sides
                // This just creates a fan from the first vertex
                Vertex v0 = model->vertices[polygon.v[0]];
                point3 p0 = center + normalizing_scale * (point3(v0.x, v0.y, v0.z) - model_center);
                
                for (int j = 1; j < polygon.noSides - 1; j++) {
                    Vertex v1 = model->vertices[polygon.v[j]];
                    Vertex v2 = model->vertices[polygon.v[j + 1]];
                    
                    point3 p1 = center + normalizing_scale * (point3(v1.x, v1.y, v1.z) - model_center);
                    point3 p2 = center + normalizing_scale * (point3(v2.x, v2.y, v2.z) - model_center);
                    
                    triangles.add(make_shared<triangle>(p0, p1, p2));
                }
            }
        }
        
        // Free the OFF model after we're done with it
        FreeOffModel(model);
    }

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        return triangles.hit(r, ray_t, rec);
    }

private:
    hittable_list triangles;
};

#endif
