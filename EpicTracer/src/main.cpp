#include <iostream>
#include "Vec3.h"
#include "Image.h"
#include "Color.h"
#include "core.h"
#include "Ray.h"
#include "Sphere.h"
#include "Object.h"
#include "Camera.h"
#include "Material.h"
#include <iomanip>
#include "LightSource.h"
#include <string>
#include <ostream>
#define _USE_MATH_DEFINES
#include <math.h>



EPIC::Image bg("ressources/background.hdr");


auto p = EPIC::Vec3<float>(-1.9f, 1.2f, -3.0f);
auto p2 = EPIC::Vec3<float>(-2.9f, 1.5f, 4.54f);

EPIC::Camera camera(p,
					p2,
					EPIC::Vec3<float>(0.0f, 1.0f, 0.0f),
					45,
					16.0f/9.0f,
					0.5f,
					(p-p2)->norm());

std::shared_ptr<EPIC::Color> rayTrace(std::shared_ptr<EPIC::Ray> ray, const EPIC::HitList& world, int depth){
	//std::cout << ray.direction().norm();

	if(depth<=0){
		return std::make_shared<EPIC::Color>("000000");
	}
	
	EPIC::HitRecord rec;
	if(world.hit(ray, 0.001f, 100000.0f, rec)){

		auto material = rec.m_material;//EPIC::Color("F57C00");
		auto reflectedRay = std::make_shared<EPIC::Ray>();
		auto attenuation = std::make_shared<EPIC::Color>();

		if(material->scatter(*ray, rec, *attenuation, *reflectedRay)){

			if (material->type == EPIC::LIGHT_MATERIAL) {
				return std::make_shared<EPIC::Color>(*(*attenuation*3.0f));
			}
			else {
				auto c = rayTrace(reflectedRay, world, depth - 1);
				return std::make_shared<EPIC::Color>(*(*attenuation * *c));
			}
		}

		return std::make_shared<EPIC::Color>("000000");
	}

	float x = (*(ray->direction()))[0];
	float y = (*(ray->direction()))[1];
	float z = (*(ray->direction()))[2];

	auto phi = atan2(-z, x) + M_PI;
	auto theta = acos(-y);

	x = phi/(2*M_PI);
	y = theta/M_PI;

	x = clamp(x, 0.0f, 1.0f);
	y = 1.0-clamp(y, 0.0f, 1.0f);

	int i = floor(y*2160);
	int j = floor(x*4096);

	return bg.getPixel(i, j);
}


int main(){

	// world
	EPIC::HitList world;

	auto color1 = std::make_shared<EPIC::Color>("212121"); // plan
	auto color2 = std::make_shared<EPIC::Color>("CCCCCC"); // silver
	auto color3 = std::make_shared<EPIC::Color>("536DFE"); // zerga
	auto color4 = std::make_shared<EPIC::Color>("E91E63"); // rose
	auto color5 = std::make_shared<EPIC::Color>("CDDC39"); // khedhra


	auto lambertian1 = std::make_shared<EPIC::Lambertian>(*color1);
	auto lambertian2 = std::make_shared<EPIC::Metal>(*color2);
	auto lambertian3 = std::make_shared<EPIC::Metal>(*color3);
	auto lambertian4 = std::make_shared<EPIC::Metal>(*color4);
	auto lambertian5 = std::make_shared<EPIC::Metal>(*color5);
	auto lightColor = std::make_shared<EPIC::LightMat>(*color2);


	//world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(-1000.0f, 0.0f, -1000.0f), 1000.0f, lambertian1));
	//world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(0.0f, 0.0f, -1.0f), 0.3f, lambertian4));
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(-5.58f, 2.5f, 9.38f), 2.5f, lambertian5));
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(3.16f, 2.0f, 5.5f), 1.0f, lambertian4));
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(-2.9f, 1.5f, 5.54f), 1.5f, lambertian3));
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(-1.5f, 1.0f, 3.6f), 1.0f, lambertian2));

	// background
	

	// flooor
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(0.0f, -300.0f, 1.0f), 300.0f, lambertian1));
	

	////top
	//world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(0.0f, 10011.0f, 0.0f), 10000.0f, lambertian1));
	////left 
	////world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(-1008.0f, 0.0f, 0.0f), 1000.0f, lambertian1));
	//// front
	//world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(0.0f, 0.0, 1010.0f), 1000.0f, lambertian1));
	//// right
	//world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(+1008.0f, 0.0f, 0.0f), 1000.0f, lambertian1));
	//// back
	////world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(0.0f, 0.0f, -1000.0f), 1000.0f, lambertian1));
	//
	//camera

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
				 //std::make_shared<EPIC::Vec3<float>>();
				 std::shared_ptr<EPIC::Vec3<float>> conversion = rayTrace(ray, world, MAX_DEPTH);
				 c = *c + *conversion;
			}

			img.getPixel(HEIGHT-i-1, WIDTH-j-1) = std::make_shared<EPIC::Color>(*c);


		    #pragma omp atomic
			++steps_completed;


			if(steps_completed%10000==1){
			#pragma omp critical
				
				std::cout<<"Progress: "<<steps_completed<<" of "<<total_steps<<" ("<< std::fixed << std::setprecision(1)<<(100.0*steps_completed/total_steps)<<"%)\n";
			}




		}
	}

	
	img.save("render.ppm");
	
	return 0;
}