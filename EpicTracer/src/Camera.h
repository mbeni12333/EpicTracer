#pragma once
#include "Vec3.h"
#include "Ray.h"
#include <memory>

namespace EPIC{
	class Camera{
		public:


		Camera(int width, int height);
		std::shared_ptr<EPIC::Ray> getRay(int i, int j) const;


		private:

		float fov;

		std::shared_ptr<Vec3<float>> origin;
		std::shared_ptr<Vec3<float>> lowerLeftCorner;

		int viewPortHeight;
		int viewPortWidth;

		// will contain {xmin, xmax, deltax}
		Vec3<float> viewPortX;
		// will contain {ymin, ymax, deltay}
		Vec3<float> viewPortY;


	};
}

