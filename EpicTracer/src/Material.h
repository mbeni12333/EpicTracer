#pragma once
#include "Color.h"
#include "Object.h"

namespace EPIC{


	class Material{
		virtual void scatter(const Vec3<float>& point) const = 0;
	};


	class UniformMaterial: public Material{
		

		virtual void scatter(const Vec3<float>& point) const override{
			//ht.position = point;
			//ht.material = this;
		}

		private:
		Color albedo;
	};

}

