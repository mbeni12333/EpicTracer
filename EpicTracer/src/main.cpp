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


auto light = EPIC::LightSource();
EPIC::Camera camera(WIDTH, HEIGHT);


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
				return attenuation;
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


	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(-1000.0f, 0.0f, -1000.0f), 1000.0f, lambertian1));
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(0.7f, 0.1f, -1.2f), 0.3f, lambertian4));
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(-0.75f, 0.0f, 1.0f), 0.5f, lambertian5));
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(0.7f, 0.1f, -1.2f), 0.3f, lambertian4));
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(0.0f, 0.0f, -1.0f), 0.3f, lambertian3));
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(0.3f, -0.1f, -1.5f), 0.2f, lambertian2));
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(0.0f, 100.5f, -1.0f), 100.0f, lambertian1));
	

	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(0.0f, -30.0f, 120.0f), 100.0f, lambertian1));
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(-105.0f, 0.0, -1.0f), 100.0f, lambertian1));
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(0.0f, -107.5f, -1.0f), 100.0f, lightColor));
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(102.0f, 103.0f, -1.0f), 100.0f, lambertian1));
	world.add(std::make_shared<EPIC::Sphere>(std::make_shared<EPIC::Vec3<float>>(0.0f, 0.0f, -120.0f), 100.0f, lambertian1));

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