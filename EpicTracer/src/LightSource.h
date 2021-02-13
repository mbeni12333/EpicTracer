#pragma once
#include "Vec3.h"
#include "Color.h"

namespace EPIC{
	class LightSource{
		public:
		LightSource():c("ffffff"), m_position(0.0f, 1.0f, 0.0f){

		}

		Color c;
		Vec3<float> m_position;
	};
}


