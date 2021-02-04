#pragma once
#include "Vec3.h"

namespace EPIC{
	class Ray{

		public:
		Ray(const Vec3<float>& origin, const Vec3<float>& direction){
			m_direction = direction;
			m_direction.normalize();
			m_origin = origin;
		}

		Vec3<float> origin(){ return m_origin; }
		Vec3<float> direction(){ return m_direction; }

		Vec3<float> pointAt(float dist){
			return m_direction*dist+m_origin;
		}
	
		private:
		Vec3<float> m_direction;
		Vec3<float> m_origin;
	};
}



