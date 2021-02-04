#pragma once
#include <vector>
#include "LightSource.h"
#include "Camera.h"
#include "Object.h"

namespace EPIC{
	class Scene{

		public:
		Scene(Camera camera,std::vector<LightSource>& lights, std::vector<Object>& objects)
			:m_camera(camera),m_lights(lights),m_objects(objects){}


		private:
		Camera m_camera;
		std::vector<LightSource> m_lights;
		std::vector<Object> m_objects;
	};
}
