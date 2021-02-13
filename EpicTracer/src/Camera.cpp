#include "Camera.h"
#include "Ray.h"
#include <memory>


namespace EPIC{

        Camera::Camera(
            const Vec3<float>& lookfrom,
            const Vec3<float>& lookat,
            const Vec3<float>& vup,
            float vfov,
            float aspect_ratio,
            float aperture,
            float focus_dist): origin(lookfrom){

            auto theta = vfov*M_PI/180.0;
            auto h = tan(theta/2);
            auto viewport_height = h;
            auto viewport_width = aspect_ratio*viewport_height;

            z = (lookfrom-lookat)->normalize();
            x = vup.cross(*z)->normalize();
            y = z->cross(*x);


            std::cout<<*x;
            std::cout<<*y;
            std::cout<<*z;

            origin = lookfrom;




            horizontal = *(*x*(focus_dist*viewport_width*2.0f));
            vertical = *(*y*(focus_dist*viewport_height*2.0f));


            lower_left_corner = *(*(*(origin-*(horizontal*0.5f))-*(vertical*0.5f))-*(*z*focus_dist));
            std::cout<<lower_left_corner;
            /*
            horizontal_unit_vec = *(horizontal_unit_vec*viewport_width);
            vertical_unit_vec = *(horizontal_unit_vec*viewport_height);
            */

            //auto plane_intersect = *(origin - *(*z*focus_dist));


            lens_radius = aperture/2;
        }

        std::shared_ptr<Ray> Camera::getRay(int i, int j) const{


            float i_n = (i+random_double())/HEIGHT;
            float j_n = (j+random_double())/WIDTH;

            auto rd = *(*random_in_unit_disk()*lens_radius);
            auto offset = *(*(*x*rd[0])+*(*y*rd[1]));

            auto shoot_pos = origin+offset;

            auto viewport_pos = *(*(lower_left_corner+
                                  *(vertical*i_n))+
                                  *(horizontal*j_n));

            return std::make_shared<Ray>(shoot_pos, viewport_pos-*shoot_pos);

        }




/*
	Camera::Camera(int width, int height){

		origin = std::make_shared<Vec3<float>>(0.0f, 0.0f, -4.0f);

		viewPortHeight = height;
		viewPortWidth = width;

		float aspectRatio = ((float)width)/((float)height);

		viewPortX[0] = -1.0f; // xmin
		viewPortX[1] = +1.0f; // xmax
		viewPortX[2] = (float)(viewPortX[1]-viewPortX[0])/(float)(width-1); // deltaX


		viewPortY[0] = -1.0f/aspectRatio; // ymin
		viewPortY[1] = +1.0f/aspectRatio; // ymax
		viewPortY[2] = (float)(viewPortY[1]-viewPortY[0])/(float)(height-1); // deltaY


		fov = -1.0f;

	}


	std::shared_ptr<EPIC::Ray> Camera::getRay(int i, int j) const{

		float y = viewPortY[0]+(i+random_double())*viewPortY[2];
		float x = viewPortX[0]+(j+random_double())*viewPortX[2];
		//std::cout<<x<<" "<<y<<std::endl;
		auto direction = EPIC::Vec3<float>(x, y, fov)-*origin;
		return std::make_shared<EPIC::Ray>(origin, direction);
	}



*/

}