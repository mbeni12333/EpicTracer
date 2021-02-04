#include <iostream>
#include "Vec3.h"
#include "Vec3.cpp"
#include "Image.h"
#include "Color.h"
#include "core.h"
#include "Ray.h"
#include "Sphere.h"

#define HEIGHT 480
#define WIDTH 640

EPIC::Sphere s(EPIC::Vec3<float>(0.0f, 0.0f, -1.0f), 0.5f);

EPIC::Color color(EPIC::Ray& ray){
	//std::cout << ray.direction().norm();
	EPIC::HitRecord rec;
	if(s.hit(ray, 0.0f, 10000.0f, rec)){
		return EPIC::Color("FFC107");
	}

	float t = 0.5*(ray.direction()[1]+1.0);
	auto white = EPIC::Color("FFFFFF");
	auto main = EPIC::Color("03a9f4");

	return main*(1.0-t) + white*t;
}

int main(){

	/*EPIC::Vec3<float> zero(1.0f, 0.0f, 0.0f);
	std::cout<<zero;

	std::cout<<"Test add 0,1,0.5 : " <<zero+EPIC::Vec3<float>(0.0f, 1.0f, 0.5f);
	std::cout<<"Test minus 0,1,0.5 : " << zero-EPIC::Vec3<float>(0.0f, 1.0f, 0.5f);
	std::cout<<"Test mult 2 : "<< zero*2;
	std::cout<<"Test div 2 : " << zero/2;

	std::cout<<"Test dot : "<<zero.dot(EPIC::Vec3<float>(0.0f, 1.0f, 1.0f))<<std::endl;
	std::cout<<"Test cross : "<<zero.cross(EPIC::Vec3<float>(0.0f, 1.0f, 1.0f));

	std::cout<<"Test norm: "<<zero.norm()<<std::endl;
	std::cout<<"Test norm: "<<zero.normalize();*/
	//Camera camera()



	EPIC::Vec3<float> lowerLeftCorner(-1.0f, -1.0f, 0.0f);
	EPIC::Vec3<float> horizontal(2.0f, 0.0f, 0.0f);
	EPIC::Vec3<float> vertical(0.0f, 2.0f, 0.0f);
	EPIC::Vec3<float> camera(0.0f, 0.0f, -5.0f);

	EPIC::Image img(WIDTH, HEIGHT);

	float aspectRatio = ((float)WIDTH)/((float)HEIGHT);

	float xmin = -1.0f;
	float xmax = +1.0f;
	float deltaX = (float)(xmax-xmin)/(float)(WIDTH-1);

	float ymin = -1.0f/aspectRatio;
	float ymax = +1.0f/aspectRatio;
	float deltaY = (float)(ymax-ymin)/(float)(HEIGHT-1);



	for(int i = 0; i<HEIGHT; i++){
		float y = ymin+i*deltaY;;
		for(int j = 0; j<WIDTH; j++){
			float x = xmin+j*deltaX;
			
			EPIC::Ray* ray = new EPIC::Ray(camera, EPIC::Vec3<float>(x, y, 0.0f) - camera);
			*(img.getPixel(i, j)) = color(*ray);
			//std::cout<<*(img.getPixel(i, j));
			delete ray;
		}
	}


	img.save("background.ppm");

	/*EPIC::Color black("000000");

	auto pixel = img.getPixel(320, 240);
	for(auto it = pixel; it<pixel+5000;it++){
		*it = black;
	}
	std::cout << black;

	img.save("image.ppm");*/



	return 0;
}