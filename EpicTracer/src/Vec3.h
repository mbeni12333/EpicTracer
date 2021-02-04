#pragma once
#include <iostream>


namespace EPIC{

	template <typename T> class Vec3{
		public:

		Vec3<T>();
		Vec3<T>(T x, T y, T z);
		Vec3<T>(const Vec3& v);

		Vec3<T>& operator+(const Vec3<T>& v);
		Vec3<T>& operator-(const Vec3<T>& v);
		Vec3<T>& operator*(const float& k);
		Vec3<T>& operator/(const float& k);
		Vec3<T>& operator+=(const Vec3<T>& v);
		Vec3<T>& operator-=(const Vec3<T>& v);
		Vec3<T>& operator*=(const float& v);

		T& operator[](int index);
		T operator[](int index) const;

		Vec3<T>& cross(const Vec3<T>& v);

		float norm();
		Vec3<T>& normalize();
		float dot(const Vec3<T>& v);
		 

		private:
		T m_data[3];


	};



	template<typename T>
	std::ostream& operator<< (std::ostream& out, Vec3<T>& v){
		out<<v[0]<<" "<<v[1]<<" "<<v[2]<<std::endl;
		return out;
	}

}



