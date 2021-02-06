#include "Camera.h"

namespace EPIC{


	Camera::Camera(int width, int height){

		origin = std::make_shared<Vec3<float>>(0.0f, 0.0f, -4.0f);

		viewPortHeight = height;
		viewPortWidth = width;

		float aspectRatio = ((float)width)/((float)height);

		viewPortX[0] = -1.0f; // xmin
		viewPortX[1] = +1.0f; // xmax
		viewPortX[2] = (float)(viewPortX[1]-viewPortX[0])/(float)(width-1); // deltaX


		viewPortY[0] = -1.0f/aspectRatio; // ymin
		viewPortY[1] = +1.0f/aspectRatio; // ymax
		viewPortY[2] = (float)(viewPortY[1]-viewPortY[0])/(float)(height-1); // deltaY


		fov = -1.0f;

	}


	std::shared_ptr<EPIC::Ray> Camera::getRay(int i, int j) const{

		float y = viewPortY[0]+(i+random_double())*viewPortY[2];
		float x = viewPortX[0]+(j+random_double())*viewPortX[2];
		//std::cout<<x<<" "<<y<<std::endl;
		auto direction = EPIC::Vec3<float>(x, y, fov)-*origin;
		return std::make_shared<EPIC::Ray>(origin, direction);
	}





}