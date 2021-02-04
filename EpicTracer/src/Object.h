#pragma once
#include "Vec3.h"
#include "Material.h"
#include "Ray.h"
#include <vector>

namespace EPIC{

	struct HitRecord{
		Vec3<float> position;
		Vec3<float> normal;
		float t;
	};


	class Hitable{
		public:
		virtual bool hit(const Ray& ray, float t_min, float t_max, HitRecord& record) const = 0;
	};


	class HitList: Hitable{

		virtual bool hit(const Ray& ray) = 0;
		virtual Vec3<float> normalAt(const Vec3<float>& point) = 0;
		virtual Vec3<float> scatter(const Vec3<float>& point) = 0;

		private:
		std::vector<Hitable*> objects;
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

