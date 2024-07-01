#include <iostream>
#include <fstream>
#include "aceheader.h"

#include "color.h"
#include "hittable_list.h"
#include "camera.h" 
#include "material.h"
#include "figures.h"


color ray_color(const ray& r, const color& background, const hittable& world, int depth) {
    hit_record rec;
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0,0,0);

        // If the ray hits nothing, return the background color.
    if (!world.hit(r, 0.001, infinity, rec)){
    	vec3 unit_direction = unit_vector(r.direction());
    	float t = 0.5*(unit_direction.y() + 1.0);
    	return (1.0-t)*background + t*color(0.8, 0.8, 0.2);
        //return background;
    }

    ray scattered;
    color attenuation;
    color emitted = rec.mat_ptr->emitted();

    if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        return emitted;

    return emitted + attenuation * ray_color(scattered, background, world, depth-1);
}


int main() {
	std::ofstream salida;
	salida.open("image.ppm");

    // Variables de la Foto
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 5000;
    const int max_depth = 50;

    // Aspectos de la escena
    auto R = cos(pi/4);
    
    hittable_list world;
    
    // Materiales y sus propiedades 
    auto tierra          = make_shared<lambertian>(color(0.48, 0.19, 0.0));
    auto rojo            = make_shared<lambertian>(color(0.7, 0.2, 0.2));
    auto azul            = make_shared<lambertian>(color(0.2, 0.2, 0.7));
    auto verde           = make_shared<lambertian>(color(0.2, 0.7, 0.2));
    auto amarillo        = make_shared<lambertian>(color(0.7, 0.7, 0.2));
    auto violeta         = make_shared<lambertian>(color(0.7, 0.2, 0.7));
    auto cyan            = make_shared<lambertian>(color(0.2, 0.7, 0.7));
    auto plateado        = make_shared<metal>(color(0.8, 0.8, 0.8), 0.9);
    auto plata           = make_shared<metal>(color(0.8, 0.8, 0.8), 0.1);
    auto rubi            = make_shared<metal>(color(0.8, 0.1, 0.1), 0);
    auto rubi_mate       = make_shared<metal>(color(0.8, 0.1, 0.1), 0.9);
    auto amatista        = make_shared<metal>(color(0.8, 0.1, 0.8), 0);
    auto amatista_mate   = make_shared<metal>(color(0.8, 0.1, 0.8), 0.9);
    auto esmeralda       = make_shared<metal>(color(0.1, 0.8, 0.1), 0);
    auto esmeralda_mate  = make_shared<metal>(color(0.1, 0.8, 0.1), 0.9);
    auto dorado          = make_shared<metal>(color(0.8, 0.8, 0.1), 0.9);
    auto oro             = make_shared<metal>(color(0.8, 0.8, 0.1), 0);
    auto material_plane  = make_shared<lambertian>(color(0.7, 0, 0));
    auto foco_azul       = make_shared<diffuse_light>(color(0, 0, 1));
    auto foco_rojo       = make_shared<diffuse_light>(color(1, 0, 0));
    auto foco_blanco     = make_shared<diffuse_light>(color(1, 1, 1));
    auto enana_blanca    = make_shared<diffuse_light>(color(100, 100, 100));
    auto enana_azul      = make_shared<diffuse_light>(color(0, 0, 100));
    auto sol_rojo        = make_shared<diffuse_light>(color(100, 0, 0));
    auto sol_amarillo    = make_shared<diffuse_light>(color(100, 100, 0));
    
    // Orden de generacion de triangulos en las diferentes mallas
    const unsigned int orden_cubo[] = {0, 1, 2, 
								   	   2, 3, 1, 
								       4, 5, 6, 
								       5, 7, 6, 
								       0, 1, 4, 
								       4, 5, 1, 
								       0, 2, 4, 
								       2, 4, 6,
								       2, 3, 6, 
								       6, 7, 3, 
								       1, 3, 7, 
								       1, 5, 7};	
	const unsigned int orden_piramide[] = {0, 1, 2, 
									       1, 2, 3, 
									       2, 3, 0, 
									       1, 3, 0};
	const unsigned int orden_icosaedro[] = {0,1,2,
											0,1,3,
											0,2,5,
											1,2,4,
											2,4,8,
											1,4,7,
											7,4,10,
											4,10,8,
											8,10,11,
											7,10,9,
											8,5,11,
											9,10,11,
											5,6,11,
											6,9,11,
											0,5,6,
											0,6,3,
											3,6,9,
											1,3,7,
											3,7,9,
											2,5,8
											};
									 
    // Conjunto de puntos
    point3 piramide1[] = {point3(1,0,0), point3(0,0,1), point3(-1,0,0), point3(0,1.5,0)};
    
    point3 piramide2[] = {point3(0.5,0,0), point3(0,0,0.5), point3(-0.5,0,0), point3(0,-1,0)};
    
    point3 cubo1[] = {point3(0,0,1), point3(1,0,0), point3(-1,0,0), point3(0,0,-1),
    				   point3(0,1.4,1), point3(1,1.4,0), point3(-1,1.4,0), point3(0,1.4,-1)};
    				   
    point3 cubo2[] = {point3(0,0,1.2), point3(1.2,0,0), point3(-1.2,0,0), point3(0,0,-1.2),
    				   point3(0,1.6,1.2), point3(1.2,1.6,0), point3(-1.2,1.6,0), point3(0,1.6,-1.2)};
   	
   	point3 cubo3[] = {point3(0,0,1), point3(1,-1,0), point3(-1,-1,0), point3(0,-2,-1),
    				   point3(0,1,1), point3(1,0,0), point3(-1,0,0), point3(0,-1,-1)};
    				   
    point3 icosaedro1[] = {point3(0,0,0), point3(0.5,0,0), point3(0.25, 0, 0.43),
    					  point3(0.25,0.29,-0.32), point3(0.65,0.29,0.38), point3(-0.15,0.29,0.38),
    					  point3(-0.15,0.47,-0.09), point3(0.65,0.47,-0.09), point3(0.25,0.47,0.61),
    					  point3(0.25,0.76,-0.14), point3(0.5,0.76,0.29), point3(0,0.76,0.29)
    					  };
    point3 icosaedro2[] = {point3(0,0,0), point3(1,0,0), point3(0.5, 0, 0.87),
    					  point3(0.5,0.58,-0.65), point3(1.31,0.29,0.38), point3(-0.15,0.29,0.38),
    					  point3(-0.15,0.47,-0.09), point3(0.65,0.47,-0.09), point3(0.25,0.47,0.61),
    					  point3(0.25,0.76,-0.14), point3(0.5,0.76,0.29), point3(0,0.76,0.29)
    					  };
    
    point3 centro_tierra = point3(0.0, -100.5, -2.0);
    float radio_tierra = 300.0;
    				 			   
    point3 centro1 = point3(0, 0, 0);
    float radio1 = 0.5;
    
    point3 centro2 = point3(0.26, 0.4, 0.2);
    float radio2 = 0.01;
         
    point3 centro3 = point3(0, 100, 0);
    float radio3 = 80;
    
    
   
	// Generacion de figuras en la escena
	incr(12, icosaedro1, 2);
    move(12, icosaedro1, 2.5, -0.3, 2.5);
    world.add(make_shared<mesh> (20, icosaedro1, orden_icosaedro, esmeralda_mate));
    
    incr(12, icosaedro1, 2);
    move(12, icosaedro1, 4, 1, -10);
    world.add(make_shared<mesh> (20, icosaedro1, orden_icosaedro, amatista));
    
    incr(12, icosaedro1, 3);
    move(12, icosaedro1, 1, 1, -10);
    world.add(make_shared<mesh> (20, icosaedro1, orden_icosaedro, sol_amarillo));
    
	movePoint(centro_tierra, 0, -200.17, 0);
    world.add(make_shared<sphere>(centro_tierra, radio_tierra, tierra));
    
    movePoint(centro1, 4, 0, -2);
    world.add(make_shared<sphere>(centro1, radio1, azul));
    
    move(4, piramide1, 1, -0.5, 1);
    world.add(make_shared<mesh> (4, piramide1, orden_piramide, oro));
    
    move(8, cubo1, -1, -0.5, 2);
    world.add(make_shared<mesh> (12, cubo1, orden_cubo, dorado));
    
    movePoint(centro1, -7, 0.5, 5);
    radio1 = 0.7;
    world.add(make_shared<sphere>(centro1, radio1, plateado));
    
    movePoint(centro1, -0.5, -0.75, -4);
    radio1 = 0.3;
    world.add(make_shared<sphere>(centro1, radio1, rojo));

    move(8, cubo2, 2, 0.25, -2);
    world.add(make_shared<mesh> (12, cubo2, orden_cubo, rubi));
    
    move(8, cubo3, 4.5, 1.5, 2);
    world.add(make_shared<mesh> (12, cubo3, orden_cubo, plata));
    
    move(4, piramide2, -5, 1.2, 3.5);
    world.add(make_shared<mesh> (4, piramide2, orden_piramide, enana_azul));
    
    world.add(make_shared<sphere> (centro3, radio3, foco_blanco));
    
    centro3 = point3(0, 1, 0);
    radio3 = 0.5;
    world.add(make_shared<sphere> (centro3, radio3, enana_blanca));
    
    centro3 = point3(0, 0.4, 7);
    radio3 = 0.1;
    world.add(make_shared<sphere> (centro3, radio3, sol_rojo));
      
    
    centro3 = point3(3.6, 0.5, 5);
    radio3 = 0.3;
    world.add(make_shared<sphere> (centro3, radio3, amatista_mate));
    
    movePoint(centro1, -0.5, 2, -4);
    radio1 = 2.3;
    world.add(make_shared<sphere>(centro1, radio1, esmeralda));

    // Aspectos de Camara

    point3 lookfrom(0,4,20);
	point3 lookat(0, 0, 0);
	vec3 vup(0,1,0);
	auto dist_to_focus = (lookfrom-lookat).length();
	auto aperture = 0.0;
	color background(0,0,0);
	background = color(0.0, 0.0, 0.8);

	camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

    // Creacion de Imagen

    salida << "P3\n" << image_width << ' ' << image_height << "\n255\n";
	double den = 1.0*image_height*image_width*samples_per_pixel;
    for (int j = image_height-1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
    			double num = image_height-j;
    			num *= image_width;
    			num += i;
    			num *= samples_per_pixel;
    			num += s;
    			num *= 100.0;
    			
            	std::cerr << "\rProgreso: " 
            	<< (num/den) << "\%" 
            	<< "           " << std::flush;
            	
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, background, world, max_depth);
            }
            write_color(salida, pixel_color, samples_per_pixel);
        }
    }
    std::cerr << "\nCompletado.\n";
}
