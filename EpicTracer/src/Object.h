#pragma once
#include "Vec3.h"
#include "Material.h"
#include "Ray.h"
#include <vector>
#include <memory>

namespace EPIC{

	struct HitRecord{
		Vec3<float> position;
		Vec3<float> normal;
		float t;
	};


	class Hitable{
		public:
		virtual bool hit(const Ray& ray, float t_min, float t_max, HitRecord& record) const{ return false; };
	};


	class HitList: Hitable{

		public:
		void add(std::shared_ptr<Hitable> obj){
			objects.push_back(obj);
		}

		virtual bool hit(const Ray& ray, float t_min, float t_max, HitRecord& record) const {

			bool hit_something = false;
			auto closest_so_far = t_max;
			HitRecord temp_rec;

			for(auto object:objects){
				if(object->hit(ray, t_min, t_max, temp_rec)){
					hit_something = true;
					if(closest_so_far>temp_rec.t){
						closest_so_far = temp_rec.t;
						record = temp_rec;
					}
				}
			}

			return hit_something;
		}

		private:
		std::vector<std::shared_ptr<Hitable>> objects;
	};


	class Object{

		public:

		virtual const Vec3<float>& normalAt(const Vec3<float>& point) const{ return point; };
		virtual const Vec3<float>& scatter(const Vec3<float>& point) const{ return point; };

		void move(const Vec3<float>& position){
			m_position = position;
		}


		protected:
		Vec3<float> m_position;		
	};



}

