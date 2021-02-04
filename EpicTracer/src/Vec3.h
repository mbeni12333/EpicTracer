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

		const Vec3<T>& operator+(const Vec3<T>& v) const;
		const Vec3<T>& operator-(const Vec3<T>& v) const;
		const Vec3<T>& operator*(const float& k) const;
		const Vec3<T>& operator/(const float& k) const;
		const Vec3<T>& operator+=(const Vec3<T>& v);
		const Vec3<T>& operator-=(const Vec3<T>& v);
		const Vec3<T>& operator*=(const float& v);


		inline static Vec3<T> random(){
			return Vec3<T>(random_double(), random_double(), random_double());
		}

		inline static Vec3<T> random(float min, float max){
			return Vec3<T>(random_double(min, max), random_double(min, max), random_double(min, max));
		}

		inline static Vec3<T> random_unit_sphere(){
			while(true){
				auto p = random(-1.0f, 1.0f);
				if(p.norm()>=1) continue;
				return p;
			}
		}

		T& operator[](int index);
		T operator[](int index) const;

		const Vec3<T>& cross(const Vec3<T>& v) const;

		float norm()  const;
		const Vec3<T>& normalize() const;
		float dot(const Vec3<T>& v) const;
		 

		protected:
		T m_data[3];


	};



	template<typename T>
	std::ostream& operator<< (std::ostream& out, Vec3<T>& v){
		out<<v[0]<<" "<<v[1]<<" "<<v[2]<<std::endl;
		return out;
	}

}



