#pragma once

#include "Vec3.h"
#include "Color.h"
#include "Ray.h"
#include "Object.h"

namespace EPIC{
	class Sphere: virtual public Object, public Hitable{

		public:
		Sphere(std::shared_ptr<Vec3<float>> origin, float radius, std::shared_ptr<Color> c):m_c(c){
			Object::m_position = origin;
			m_radius = radius;
		}


		virtual std::shared_ptr<Vec3<float>> normalAt(const Vec3<float>& point) const {
			return (*Object::m_position - point)->normalize();
		}


		virtual const Vec3<float>& scatter(const Vec3<float>& point) const {
			return point;
		}


		virtual bool hit(std::shared_ptr<Ray> ray, float t_min, float t_max, HitRecord& record) const{

			auto sphereToRay = (*ray->origin()) - (*m_position);
			//std::cout<<"Sphere to ray: " << sphereToRay;
			float b = sphereToRay->dot(*ray->direction())*2.0;
			//std::cout<<"b = "<<b<<std::endl;
			float c = sphereToRay->dot(*sphereToRay) - m_radius*m_radius;
			//std::cout<<"c = "<<c<<std::endl;
			float delta = b*b-4*c;
			//std::cout<<"delta = "<<delta<<std::endl;
			if(delta<0)
				return false;

			auto sqrt_d = sqrt(delta);
			auto root = (float)(-b-sqrt_d)/2.0f;

			if(root < t_min||root > t_max){
				root = (float)(-b+sqrt_d)/2.0f;
				if(root < t_min||root > t_max){
					return false;
				}
			}

			record.t = root;
			record.position = ray->pointAt(root);
			record.normal = normalAt(*record.position);
			record.c = m_c;

			return true;
		}

		inline std::shared_ptr<Color> getColor(){ return m_c; };

		private:
		float m_radius;
		std::shared_ptr<Color> m_c;
	};
}


