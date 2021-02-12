#pragma once
#include "Vec3.h"
#include "Ray.h"
#include <memory>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>



namespace EPIC{



    


    class Camera{
        public:
        Camera(
            const Vec3<float>& lookfrom,
            const Vec3<float>& lookat,
            const Vec3<float>& vup,
            float vfov,
            float aspect_ratio,
            float aperture,
            float focus_dist);

        inline static std::shared_ptr<Vec3<float>> random_in_unit_disk(){

            auto p = std::make_shared<EPIC::Vec3<float>>((random_double()-0.5f)*2.0, (random_double()-0.5f)*2.0f, 0);
            do{
                p = std::make_shared<EPIC::Vec3<float>>((random_double()-0.5f)*2.0, (random_double()-0.5f)*2.0f, 0);
                
            } while(p->dot(*p) >= 1.0f);
            //std::cout<<"Fuck";
            return p;
        }

        std::shared_ptr<Ray> getRay(int i, int j) const;

        private:
        Vec3<float> origin;
        Vec3<float> lower_left_corner;
        Vec3<float> horizontal, vertical;

        std::shared_ptr<Vec3<float>> x, y, z;
        float lens_radius;
    };



    /*

	class Camera{
		public:


		Camera(int width, int height);
		std::shared_ptr<EPIC::Ray> getRay(int i, int j) const;


		//private:

		float fov;

		std::shared_ptr<Vec3<float>> origin;
		std::shared_ptr<Vec3<float>> lowerLeftCorner;

		int viewPortHeight;
		int viewPortWidth;

		// will contain {xmin, xmax, deltax}
		Vec3<float> viewPortX;
		// will contain {ymin, ymax, deltay}
		Vec3<float> viewPortY;


	};*/
}

