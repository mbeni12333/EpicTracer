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
#include <iomanip>



std::shared_ptr<EPIC::Color> rayTrace(std::shared_ptr<EPIC::Ray> ray, const EPIC::HitList& world, int depth){
	//std::cout << ray.direction().norm();

	if(depth<=0){
		return std::make_shared<EPIC::Color>("000000");
	}
	
	EPIC::HitRecord rec;
	if(world.hit(ray, 0.0001f, 100000.0f, rec)){
		//return EPIC::Color("FFC107");
		//return std::make_shared<EPIC::Color>(*((*(EPIC::Vec3<float>(1.0f, 1.0f, 1.0f) + *rec.normal))*0.5f));
		auto p = *(*rec.position + *rec.normal) + *EPIC::Vec3<float>::random_unit_vector();
		auto reflectedRay = std::make_shared<EPIC::Ray>(rec.position, *rec.position-*p);
		auto c = rayTrace(reflectedRay, world, depth-1);

		return std::make_shared<EPIC::Color>(*((*c)*0.5f));
	}

	float y = (*(ray->direction()))[1];
	float t = 0.5f*(y+1.0f);
	auto white = std::make_shared<EPIC::Color>("FFFFFF");
	auto main = std::make_shared<EPIC::Color>("03a9f4");
	auto background = *((*main)*(1.0f-t)) + *((*white)*t);

	

	return std::make_shared<EPIC::Color>(*background);
}


int main(){

	// world
	EPIC::HitList world;
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(0.0f, 0.0f, -1.0f), 0.5f));
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(0.5f, 0.2f, -1.5f), 0.2f));
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(0.0f, 100.5f, -1.0f), 100.0f));


	//camera
	EPIC::Camera camera(WIDTH, HEIGHT);
	EPIC::Image img(WIDTH, HEIGHT);

	auto total_steps = HEIGHT*WIDTH;

	size_t steps_completed = 0;


    #pragma omp parallel for
	for(int i = 0; i<HEIGHT; i++){
		for(int j = 0; j<WIDTH; j++){
		    //#pragma omp parallel for 
			auto c = std::make_shared<EPIC::Vec3<float>>();
			for(int sample = 0; sample<SAMPLES_PER_PIXEL; sample++){
				auto ray = camera.getRay(i, j);
				 std::make_shared<EPIC::Vec3<float>>();
				 std::shared_ptr<EPIC::Vec3<float>> conversion = rayTrace(ray, world, MAX_DEPTH);
				 c = *c + *conversion;
			}

			img.getPixel(i, j) = std::make_shared<EPIC::Color>(*c);


		    #pragma omp atomic
			++steps_completed;


			if(steps_completed%100000==1){
			#pragma omp critical
				std::cout<<"Progress: "<<steps_completed<<" of "<<total_steps<<" ("<< std::fixed << std::setprecision(1)<<(100.0*steps_completed/total_steps)<<"%)\n";
			}




		}
	}


	img.save("background.ppm");

	return 0;
}