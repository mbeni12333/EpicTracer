#include "Color.h"
#include "Vec3.h"
#include "Vec3.cpp"
#include <string>

#include "core.h"

namespace EPIC{

	Color::Color():Vec3<int>(std::stoi(DEFAULT_COLOR.substr(0, 2), 0, 16),
							 std::stoi(DEFAULT_COLOR.substr(2, 2), 0, 16),
							 std::stoi(DEFAULT_COLOR.substr(4, 2), 0, 16)){}

	Color::Color(const Vec3<int>& v):Vec3<int>(v){}
	Color::Color(int r, int g, int b) : Vec3<int>(r, g, b){}
	Color::Color(const std::string& hex): Vec3<int>(std::stoi(hex.substr(0, 2), 0, 16),
													std::stoi(hex.substr(2, 2), 0, 16),
													std::stoi(hex.substr(4, 2), 0, 16)){}
}