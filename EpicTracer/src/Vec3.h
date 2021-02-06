#pragma once
#include <iostream>
#include <random>
#include "core.h"


namespace EPIC{

	template <typename T> class Vec3{
		public:

		Vec3<T>();
		Vec3<T>(T x, T y, T z);
		Vec3<T>(const Vec3& v);

		std::shared_ptr<Vec3<T>> operator+(const Vec3<T>& v) const;
		std::shared_ptr<Vec3<T>> operator-(const Vec3<T>& v) const;
		std::shared_ptr<Vec3<T>> operator*(const float& k) const;
		std::shared_ptr<Vec3<T>> operator/(const float& k) const;
		std::shared_ptr<Vec3<T>> operator+=(const Vec3<T>& v);
		std::shared_ptr<Vec3<T>> operator-=(const Vec3<T>& v);
		std::shared_ptr<Vec3<T>> operator*=(const float& v);


		inline static std::shared_ptr<Vec3<T>> random(){
			return std::make_unique<Vec3<T>>(random_double(), random_double(), random_double());
		}

		inline static std::shared_ptr<Vec3<T>> random(float min, float max){
			return std::make_shared<Vec3<T>>(random_double(min, max),
											 random_double(min, max),
											 random_double(min, max));
		}

		inline static std::shared_ptr<Vec3<T>> random_unit_sphere(){
			while(true){
				auto p = random(-1.0f, 1.0f);
				if(p->norm()>=1) continue;
				return p;
			}
		}

		inline static std::shared_ptr<Vec3<T>> random_unit_vector(){
			return random_unit_sphere()->normalize();
		}

		T& operator[](int index);
		T operator[](int index) const;

		std::shared_ptr<Vec3<T>> cross(const Vec3<T>& v) const;

		float norm()  const;
		std::shared_ptr<Vec3<T>> normalize();
		float dot(const Vec3<T>& v) const;
		 

		protected:
		T m_data[3];


	};



	template<typename T>
	std::ostream& operator<< (std::ostream& out, const Vec3<T>& v){
		out<<v[0]<<" "<<v[1]<<" "<<v[2]<<std::endl;
		return out;
	}

}



