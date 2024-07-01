#ifndef PLANE_H
#define PLANE_H

//#include "hittable.h"
#include "hittable_list.h"
#include "vec3.h"
#include <vector>

hittable_list xd;

class triangle : public hittable{
	public:
		triangle() {}
		triangle(point3 p1, point3 p2, point3 p3, shared_ptr<material> m): mat_ptr(m) {
			vertex[0] = p1;
			vertex[1] = p2;
			vertex[2] = p3;
			normal = unit_vector(cross(vertex[0]-vertex[1], vertex[1]-vertex[2]));
		}
		
		virtual bool insideOnTriangle(const point3& p) const;
		
		virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
		
	public:
		point3 vertex[3];
		vec3 normal;
		shared_ptr<material> mat_ptr;
};

bool triangle::insideOnTriangle(const point3& p) const{
    vec3 p_vec = (vec3) p;
  	vec3 a = vertex[0] - p_vec;
	vec3 b = vertex[1] - p_vec;
  	vec3 c = vertex[2] - p_vec;
	
	vec3 u = cross(c, a);
  	vec3 v = cross(b, c);
  	vec3 w = cross(a, b);
  	
  	if (dot(u, v) < 0.0) 
      	return false;
      	
    if (dot(u, w) < 0.0) 
      	return false;
    	
  	return true;
}

bool triangle::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	vec3 n_normal = dot(normal, r.direction()) > 0 ? normal : -normal;
	
    float denom = dot(n_normal, r.direction());
    float nume = dot(n_normal, vertex[0] - r.origin());

    // Prevent divide by zero:
    if (abs(denom) <= 1e-4)
        return false;

    // If you want to ensure the ray reflects off only
    // the "top" half of the plane, use this instead:
    //
    // if (-denom <= 1e-4f)
    //     return std::nullopt;

    float t = nume / denom;
    
    // Use pointy end of the ray.
    // It is technically correct to compare t < 0,
    // but that may be undesirable in a raytracer.
    if (t_max < t || t < t_min)
        return false;
        
    if (!insideOnTriangle(r.at(t)))
    	return false;
        
	rec.t = t;
    rec.p = r.at(rec.t);
    vec3 outward_normal = n_normal;
    rec.set_face_normal(r, outward_normal);
	rec.mat_ptr = mat_ptr;
    return true;
}



class pyramid : public hittable_list{
	public:
		pyramid(){}
		pyramid(point3 *vert,  shared_ptr<material> m){
			hittable_list::add(make_shared<triangle>(vert[0], vert[1], vert[2], m));
			hittable_list::add(make_shared<triangle>(vert[1], vert[2], vert[3], m));
			hittable_list::add(make_shared<triangle>(vert[2], vert[3], vert[0], m));
			hittable_list::add(make_shared<triangle>(vert[1], vert[3], vert[0], m));
		}
};


class cube : public hittable_list{
	public:
		cube(){}
		cube(point3 *vert, shared_ptr<material> m){
			//generamos la base inferior 0123
			hittable_list::add(make_shared<triangle>(vert[0], vert[1], vert[2], m));
			hittable_list::add(make_shared<triangle>(vert[2], vert[3], vert[1], m));
			//generamos la base superior 4567
			hittable_list::add(make_shared<triangle>(vert[4], vert[5], vert[6], m));
			hittable_list::add(make_shared<triangle>(vert[5], vert[7], vert[6], m));
			//generamos la cara frontal 0145
			hittable_list::add(make_shared<triangle>(vert[0], vert[1], vert[4], m));
			hittable_list::add(make_shared<triangle>(vert[4], vert[5], vert[1], m));
			//generamos la cara lateral 0246
			hittable_list::add(make_shared<triangle>(vert[0], vert[2], vert[4], m));
			hittable_list::add(make_shared<triangle>(vert[2], vert[4], vert[6], m));
			//generamos la cara frontal 2367
			hittable_list::add(make_shared<triangle>(vert[2], vert[3], vert[6], m));
			hittable_list::add(make_shared<triangle>(vert[6], vert[7], vert[3], m));
			//generamos la cara frontal 1375
			hittable_list::add(make_shared<triangle>(vert[1], vert[3], vert[7], m));
			hittable_list::add(make_shared<triangle>(vert[1], vert[5], vert[7], m));
		
		}
};

class mesh : public hittable_list{
	public:
		mesh(){}
		mesh(int n, point3 *vert, const unsigned int *orden, shared_ptr<material> m){
			for(int i=0; i<n; i++){
				hittable_list::add(make_shared<triangle>(vert[orden[3*i]], 
														 vert[orden[3*i+1]], 
														 vert[orden[3*i+2]], m));
			}
		}
};


/*

class polygon : public hittable{
	public:
		polygon() {}
		polygon(int n, point3 *vert, shared_ptr<material> m): n_triangles(n), mat_ptr(m) {
			for(int i = 0; i < n_triangles; i++){
				point3 t[] = {vert[3*i], vert[3*i+1], vert[3*i+2]};
				tri.push_back(triangle(t, m));
			}
		}
		
		virtual bool insideOnPolygon(const point3& p) const;
		
		virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const ;
		
	public:
		int n_triangles;
		std::vector<triangle> tri;
		shared_ptr<material> mat_ptr;
};

bool polygon::insideOnPolygon(const point3& p) const{
	if (tri.size() == 0)
		return false;
	for(int i = 0; i < n_triangles; i++){
		if (tri[i].insideOnTriangle(p))
    		return true;
	}
  	return false;
}

bool polygon::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	if (tri.size() == 0)
		return false;
	for(int i = 0; i < n_triangles; i++){
		if(tri[0].hit(r, t_min, t_max, rec))
			return true;
	}
    return false;
}


class quad : public hittable{
	public:
		quad() {}
		quad(point3 *vert, shared_ptr<material> m): mat_ptr(m) {
			for (int i=0; i < 2; i++){
			 	point3 t[] = {vert[3*i], vert[3*i+1], vert[3*i+2]};
			 	tri[i] = triangle(t, m);
			}
		}
		
		virtual bool insideOnQuad(const point3& p) const;
		
		virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const ;
		
	public:
		triangle tri[2];
		shared_ptr<material> mat_ptr;
};

bool quad::insideOnQuad(const point3& p) const{
    if (tri[0].insideOnTriangle(p))
    	return true;
    if (tri[1].insideOnTriangle(p))
    	return true;
  	return false;
}

bool quad::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {

	if(tri[0].hit(r, t_min, t_max, rec))
		return true;
	if(tri[1].hit(r, t_min, t_max, rec))
		return true;
    return false;
}*/


#endif
