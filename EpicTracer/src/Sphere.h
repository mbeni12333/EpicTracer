#pragma once

#include "Vec3.h"
#include "Color.h"
#include "Ray.h"

namespace EPIC{
	class Sphere{
		public:
		Sphere(const Vec3<float>& origin, float radius){
			m_position = origin;
			m_radius = radius;
		}


		bool hit_sphere(const Ray& ray){
			Vec3<float> sphereToRay = ray.origin()-m_position;
			//std::cout<<"Sphere to ray: " << sphereToRay;
			std::cout<<"direction = "<< sphereToRay.dot(ray.direction()) <<std::endl;
			double b = sphereToRay.dot(ray.direction())*2.0;
			//std::cout<<"b = "<<b<<std::endl;
			double c = sphereToRay.dot(sphereToRay) - m_radius*m_radius;
			//std::cout<<"c = "<<c<<std::endl;
			double delta = b*b-4*c;
			//std::cout<<"delta = "<<delta<<std::endl;

			return (delta>0);
		}


		private:
		Vec3<float> m_position;
		float m_radius;
	};
}


