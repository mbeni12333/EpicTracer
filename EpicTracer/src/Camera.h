#pragma once
#include "Vec3.h"
#include "Ray.h"
#include <memory>

namespace EPIC{
	class Camera{
		public:


		Camera(int width, int height){


			origin[0] = 0.0f;
			origin[1] = 0.0f;
			origin[2] = -4.0f;
			origin[2] = -4.0f;
			origin[2] = -4.0f;

			viewPortHeight = height;
			viewPortWidth = width;

			float aspectRatio = ((float)width)/((float)height);

			viewPortX[0] = -1.0f; // xmin
			viewPortX[1] = +1.0f; // xmax
			viewPortX[2] = (float)(viewPortX[1]-viewPortX[0])/(float)(width-1); // deltaX


			viewPortY[0] = -1.0f/aspectRatio; // ymin
			viewPortY[1] = +1.0f/aspectRatio; // ymax
			viewPortY[2] = (float)(viewPortY[1]-viewPortY[0])/(float)(height-1); // deltaY


			fov = 0.0f;

		}


		std::shared_ptr<EPIC::Ray> getRay(int i, int j) const{

			float y = viewPortY[0]+(i+random_double())*viewPortY[2];
			float x = viewPortX[0]+(j+random_double())*viewPortX[2];
			//std::cout<<x<<" "<<y<<std::endl;
			return std::make_shared<EPIC::Ray>(origin, EPIC::Vec3<float>(x, y, fov)-origin);
		}



		private:

		float fov;

		Vec3<float> origin;
		Vec3<float> lowerLeftCorner;

		int viewPortHeight;
		int viewPortWidth;

		// will contain {xmin, xmax, deltax}
		Vec3<float> viewPortX;
		// will contain {ymin, ymax, deltay}
		Vec3<float> viewPortY;


	};
}

