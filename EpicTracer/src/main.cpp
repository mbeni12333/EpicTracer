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



auto light = EPIC::LightSource();
//EPIC::Camera camera(WIDTH, HEIGHT);

auto p = EPIC::Vec3<float>(0.0f, 1.2f, -12.0f);
auto p2 = EPIC::Vec3<float>(-2.9f, 1.5f, 2.54f);

EPIC::Camera camera(p,
					p2,
					EPIC::Vec3<float>(0.0f, 1.0f, 0.0f),
					45,
					16.0f/9.0f,
					1.5f,
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
				return std::make_shared<EPIC::Color>(*(*attenuation*10.0f));
			}
			else {
				auto c = rayTrace(reflectedRay, world, depth - 1);
				return std::make_shared<EPIC::Color>(*(*attenuation * *c));
			}
		}

		return std::make_shared<EPIC::Color>("111111");
	}

	float y = (*(ray->direction()))[0];
	float t = 0.9f*(y+1.0f);
	auto white = std::make_shared<EPIC::Color>("ffffff");
	auto main = std::make_shared<EPIC::Color>("B2EBF2");
	auto background = *((*white)*(1.0f-t)) + *((*main)*t);


	
	//return std::make_shared<EPIC::Color>("000000");
	return std::make_shared<EPIC::Color>(*background);
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
	auto lambertian4 = std::make_shared<EPIC::Lambertian>(*color4);
	auto lambertian5 = std::make_shared<EPIC::Metal>(*color5);
	auto lightColor = std::make_shared<EPIC::LightMat>(*color2);


	//world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(-1000.0f, 0.0f, -1000.0f), 1000.0f, lambertian1));
	//world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(0.0f, 0.0f, -1.0f), 0.3f, lambertian4));
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(-6.58f, 2.6f, 7.38f), 2.5f, lambertian5));
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(3.16f, 2.0f, 5.5f), 1.5f, lambertian4));
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(-2.9f, 1.5f, 2.54f), 1.5f, lambertian3));
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(0.0f, 1.3f, 0.6f), 1.0f, lambertian2));

	// flooor
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(0.0f, -300.0f, -1.0f), 300.0f, lambertian1));
	
	
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(-8.25f, 5.0f, 10.05), 1.7f, lightColor));
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(0.0f, 15.0f, 7.0f), 5.0f, lightColor));
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(+6.35f, -0.5f, 9.96f), 1.3f, lightColor));
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(-6.395f, -0.5f, -0.87f), 1.1f, lightColor));
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(-8.5f, 3.0f, -1.3f), 1.5f, lightColor));
	//world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(-0.875f, +0.8f, 2.0f), 0.1f, lightColor));
	//world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(0.0f, 0.5f, -1.2f), 0.2f, lightColor));
	
	
	//top
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(0.0f, 10011.0f, 0.0f), 10000.0f, lambertian1));
	//left 
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(-1008.0f, 0.0f, 0.0f), 1000.0f, lambertian1));
	// front
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(0.0f, 0.0, 1010.0f), 1000.0f, lambertian1));
	// right
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(+1008.0f, 0.0f, 0.0f), 1000.0f, lambertian1));
	// back
	//world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(0.0f, 0.0f, -1000.0f), 1000.0f, lambertian1));
	
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
				
				/*std::string s = "background_";
				s += std::to_string(i);
				s += "_";
				s += std::to_string(j);
				s += ".ppm";*/
				
				//img.save("background.ppm");
			}




		}
	}


	img.save("background.ppm");

	return 0;
}