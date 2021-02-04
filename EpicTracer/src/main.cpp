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

EPIC::Sphere s(EPIC::Vec3<float>(0, 0, -10), 0.1f);

EPIC::Color color(const EPIC::Ray& ray){
	std::cout << ray.direction();
	if(s.hit_sphere(ray)){
		return EPIC::Color("FF0000");
	}

	float t = 0.5*(ray.direction()[1]+1.0);
	auto white = EPIC::Color("FFFFFF");
	auto main = EPIC::Color("E64A19");

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



	EPIC::Vec3<float> lowerLeftCorner(-2.0f, -1.0f, -1.0f);
	EPIC::Vec3<float> horizontal(4.0f, 0.0f, 0.0f);
	EPIC::Vec3<float> vertical(0.0f, 2.0f, 0.0f);
	EPIC::Vec3<float> camera(0.0f, 0.0f, 0.0f);

	EPIC::Image img(WIDTH, HEIGHT);

	for(int i = 0; i<HEIGHT; i++){
		for(int j = 0; j<WIDTH; j++){
			
			float x = (float)j/(float)WIDTH;
			float y = (float)i/(float)HEIGHT;
			EPIC::Ray* ray = new EPIC::Ray(camera, (lowerLeftCorner + horizontal*x+vertical*y));
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