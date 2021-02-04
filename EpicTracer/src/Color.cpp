#include "Color.h"
#include "Vec3.h"
#include "Vec3.cpp"
#include <string>

#include "core.h"


int clamp(float c){
	int o = c*255;
	o = MAX(0, o);
	return MIN(o, 255);
}


namespace EPIC{

	Color::Color():Vec3<int>(std::stoi(DEFAULT_COLOR.substr(0, 2), 0, 16),
							 std::stoi(DEFAULT_COLOR.substr(2, 2), 0, 16),
							 std::stoi(DEFAULT_COLOR.substr(4, 2), 0, 16)){}

	Color::Color(const Vec3<int>& v):Vec3<int>(v){}
	Color::Color(const Vec3<float>& v):Vec3<int>(){
		Vec3::m_data[0] = clamp(v[0]);
		Vec3::m_data[1] = clamp(v[1]);
		Vec3::m_data[2] = clamp(v[2]);
	}
	Color::Color(int r, int g, int b) : Vec3<int>(r, g, b){}
	Color::Color(const std::string& hex): Vec3<int>(std::stoi(hex.substr(0, 2), 0, 16),
													std::stoi(hex.substr(2, 2), 0, 16),
													std::stoi(hex.substr(4, 2), 0, 16)){}
}