#pragma once
#include "Vec3.h"

namespace EPIC{
	class Ray{

		public:
		Ray(std::shared_ptr<Vec3<float>> origin, std::shared_ptr<Vec3<float>> direction){
			m_direction = direction->normalize();
			m_origin = origin;

		}

		std::shared_ptr<Vec3<float>> origin() const { return m_origin; }
		std::shared_ptr<Vec3<float>> direction() const { return m_direction; }

		std::shared_ptr<Vec3<float>> pointAt(float dist) const{
			return *(*(m_direction)*dist) + (*m_origin);
		}
	
		private:
		std::shared_ptr<Vec3<float>> m_direction;
		std::shared_ptr<Vec3<float>> m_origin;
	};
}



