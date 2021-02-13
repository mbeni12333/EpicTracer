#pragma once
#include "Vec3.h"
#include <string>
#include <iostream>

inline float clamp(float c, float min, float max){
	if(c>max)
		return max;
	if(c<min)
		return min;
	return c;
}

namespace EPIC{

	class Color: public Vec3<float>{
		public:
		Color():Vec3<float>(0.0f, 0.0f, 0.0f){}
		Color(const Vec3<float>& v) : Vec3<float>(v){}
		Color(float r, float g, float b) : Vec3<float>(r, g, b){}
		Color(const std::string& hex) : Vec3<float>((float)std::stoi(hex.substr(0, 2), 0, 16)/256.0f,
													(float)std::stoi(hex.substr(2, 2), 0, 16)/256.0f,
													(float)std::stoi(hex.substr(4, 2), 0, 16)/256.0f){
		
		}

		/*inline std::shared_ptr<Color> gammaCorrect(){

			auto scale = 1.0f/SAMPLES_PER_PIXEL;

			float r = sqrt(scale*m_data[0]);
			float g = sqrt(scale*m_data[1]);
			float b = sqrt(scale*m_data[2]);

			return std::make_shared<Color>(255.0f*clamp(r, 0.0f, 1.0f),
										   255.0f*clamp(g, 0.0f, 1.0f),
										   255.0f*clamp(b, 0.0f, 1.0f));
		}*/

		friend std::ostream& operator<< (std::ostream& out, const Color& v){

			auto scale = 1.0f/SAMPLES_PER_PIXEL;

			float r = sqrt(scale*v[0]);
			float g = sqrt(scale*v[1]);
			float b = sqrt(scale*v[2]);

			out<<static_cast<int>(255.0f*clamp(r, 0.0f, 1.0f))<<" "
			   <<static_cast<int>(255.0f*clamp(g, 0.0f, 1.0f))<<" "
			   <<static_cast<int>(255.0f*clamp(b, 0.0f, 1.0f))<<" ";
			return out;
		}
		
	};



}


