#pragma once
#include "Vec3.h"
#include <string>
#include <iostream>

int clamp(float c);

namespace EPIC{

	class Color: public Vec3<int>{
		public:
		Color();
		Color(int r, int g, int b);
		Color(const Vec3<int>& v);
		Color(const Vec3<float>& v);
		Color(const std::string& hex);

		inline Color* gammaCorrect(){
			return new Color(clamp(sqrt((float)m_data[0]/(256.0f*SAMPLES_PER_PIXEL))),
							 clamp(sqrt((float)m_data[1]/(256.0f*SAMPLES_PER_PIXEL))),
							 clamp(sqrt((float)m_data[2]/(256.0f*SAMPLES_PER_PIXEL))));;
		}
		
	};
}


