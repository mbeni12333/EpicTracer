#pragma once
#include "Color.h"


namespace EPIC{
	class Material{

		virtual void scatter() = 0;

		private:
		Color albedo;
	};

}

