#pragma once
#include "Vec3.h"
#include <string>

namespace EPIC{

	class Color: public Vec3<int>{
		public:
		Color();
		Color(int r, int g, int b);
		Color(const Vec3<int>& v);
		Color(const std::string& hex);

		
	};
}


