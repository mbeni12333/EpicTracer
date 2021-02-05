#include <iostream>
#include "Vec3.h"
#include "Vec3.cpp"
#include "Image.h"
#include "Color.h"
#include "core.h"
#include "Ray.h"
#include "Sphere.h"
#include "Object.h"
#include "Camera.h"




EPIC::Color color(const EPIC::Ray& ray, const EPIC::HitList& world, int depth){
	//std::cout << ray.direction().norm();

	if(depth<=0){
		return EPIC::Color("000000");
	}

	EPIC::HitRecord rec;
	if(world.hit(ray, 0.0001f, 100000.0f, rec)){
		//return EPIC::Color("FFC107");
		//return EPIC::Color(((EPIC::Vec3<float>(1.0f, 1.0f, 1.0f) + rec.normal))*0.5f);
		auto p = rec.position + rec.normal + EPIC::Vec3<float>::random_unit_vector();
		return color(EPIC::Ray(rec.position, rec.position-p), world, depth-1)*0.5f;
	}

	float t = 0.5*(ray.direction()[1]+1.0);
	auto white = EPIC::Color("FFFFFF");
	auto main = EPIC::Color("03a9f4");


	return main*(1.0-t) + white*t;
}


//void raysamples(int i, int j, EPIC::Color* pixel, const EPIC::Camera& camera, const EPIC::HitList& world){
//	for(int sample = 0; sample<SAMPLES_PER_PIXEL; sample++){
//		auto ray = camera.getRay(i, j);
//		*pixel += color(*ray, world, MAX_DEPTH); 
//	}
//}

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

	// world
	EPIC::HitList world;
	world.add(std::make_shared<EPIC::Sphere>(EPIC::Vec3<float>(0.0f, 0.0f, -1.0f), 0.5f));
	world.add(std::make_shared<EPIC::Sphere>(EPIC::Vec3<float>(0.0f, 100.5f, -1.0f), 100.0f));


	//camera
	//EPIC::Vec3<float> lowerLeftCorner(-1.0f, -1.0f, 0.0f);
	//EPIC::Vec3<float> horizontal(2.0f, 0.0f, 0.0f);
	//EPIC::Vec3<float> vertical(0.0f, 2.0f, 0.0f);
	//EPIC::Vec3<float> camera(0.0f, 0.0f, -10.0f);
	EPIC::Camera camera(WIDTH, HEIGHT);


	EPIC::Image img(WIDTH, HEIGHT);

	float aspectRatio = ((float)WIDTH)/((float)HEIGHT);

	float xmin = -1.0f;
	float xmax = +1.0f;
	float deltaX = (float)(xmax-xmin)/(float)(WIDTH-1);

	float ymin = -1.0f/aspectRatio;
	float ymax = +1.0f/aspectRatio;
	float deltaY = (float)(ymax-ymin)/(float)(HEIGHT-1);


    #pragma omp parallel for
	for(int i = 0; i<HEIGHT; i++){
		for(int j = 0; j<WIDTH; j++){
		    //#pragma omp parallel for 
			for(int sample = 0; sample<SAMPLES_PER_PIXEL; sample++){
				auto ray = camera.getRay(i, j);
				*(img.getPixel(i, j)) += color(*ray, world, MAX_DEPTH);
			}

			 

			/*if(i%200 == 0)
			std::cout<<"i = "<<i<<"; j= "<<j<<std::endl;*/
			//raysamples(i, j, (img.getPixel(i, j)), camera, world);
			//std::cout<<*(img.getPixel(i, j));
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